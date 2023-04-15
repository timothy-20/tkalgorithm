//
// Created by 임정운 on 2023/04/10.
//

#include <binary_search_tree.h>

namespace tk {
    // 배열 기반 이진 탐색 트리 구현
    template <typename t>
    array_based_bst<t>::array_based_bst(size_t size) :
     _size(size),
     _tree(new t[size]) {
         std::fill(this->_tree, this->_tree + this->_size, t());
    }

    template <typename t>
    array_based_bst<t>::~array_based_bst() {
        delete[] this->_tree;
    }

    template <typename t>
    size_t array_based_bst<t>::get_child_index(size_t index, direction direction) const {
        switch (direction) {
            case direction::none: return index;
            case direction::left: return 2 * index + 1;
            case direction::right: return 2 * index + 2;
        }
    }

    template <typename t>
    bool array_based_bst<t>::is_exist(size_t index) const {
        return index < this->_size && this->_tree[index] != t();
    }

    template <typename t>
    void array_based_bst<t>::resize(size_t new_size) {
        if (this->_tree == nullptr) {
            return;
        }

        auto new_tree(new t[new_size]);
        auto end(std::copy(this->_tree, this->_tree + (new_size >= this->_size ? this->_size : new_size), new_tree));
        std::fill(end, new_tree + new_size, t());

        delete[] this->_tree;

        this->_tree = new_tree;
        this->_size = new_size;
    }

    template <typename t>
    void array_based_bst<t>::remove_at(size_t index) { // remove 함수에 대한 도우미 함수
        while (this->is_exist(index)) { // 노드의 인덱스가 유효할 때까지 순회
            auto left_node_index(this->get_child_index(index, direction::left));
            auto right_node_index(this->get_child_index(index, direction::right));

            if (!this->is_exist(left_node_index) && !this->is_exist(right_node_index)) { // 리프 노드 인덱스의 경우
                this->_tree[index] = t();

                return;

            } else if (!this->is_exist(left_node_index) ^ !this->is_exist(right_node_index)) { // 자식 노드가 1개만 있는 경우
                auto next_node_index(this->is_exist(left_node_index) ? left_node_index : right_node_index);
                this->_tree[index] = this->_tree[next_node_index];
                index = next_node_index;
            }
        }
    }

    template <typename t>
    void array_based_bst<t>::search(t const& value, std::function<void(size_t parent, size_t current, direction direction)> const& completion) const {
        if (this->_tree[0] == t()) {
            completion(0, 0, direction::none);

            return;
        }

        size_t parent_index(0);
        size_t current_index(0);
        auto direction(direction::none);

        while (current_index < this->_size) { // 트리의 크기를 넘지 않을 때까지 순회
            if (this->_tree[current_index] == value) { // 값에 해당하는 노드 인덱스에 도달한 경우
                break;
            }

            parent_index = current_index;
            direction = this->_tree[parent_index] > value ? direction::left : direction::right; // 값이 순회 도중의 노드 인덱스의 값보다 작은 경우 왼쪽, 큰 경우 오른쪽으로 설정
            current_index = this->get_child_index(parent_index, direction);
        }

        completion(parent_index, current_index, direction);
    }

    template <typename t>
    size_t array_based_bst<t>::search_extrema(size_t root, extrema extrema) const {
        if (!this->is_exist(root)) {
            return 0;
        }

        auto current_index(root);
        auto direction(extrema == extrema::min ? direction::left : direction::right);

        do {
            current_index = this->get_child_index(current_index, direction);
        } while (current_index < this->_size);

        return current_index;
    }

    template <typename t>
    void array_based_bst<t>::traversal_preorder(size_t root, std::function<void(t& value)> const& completion) const {
        auto index_stack(new size_t[this->_size]);
        long index_stack_cursor(0);
        index_stack[index_stack_cursor] = 0;

        while (index_stack_cursor >= 0) {
            auto current_index(index_stack[index_stack_cursor--]);

            if (!this->is_exist(current_index)) {
                continue;
            }

            completion(this->_tree[current_index]);

            auto right_child_index(this->get_child_index(current_index, direction::right));
            auto left_child_index(this->get_child_index(current_index, direction::left));

            if (right_child_index < this->_size) {
                index_stack[++index_stack_cursor] = right_child_index;
            }

            if (left_child_index < this->_size) {
                index_stack[++index_stack_cursor] = left_child_index;
            }
        }

        delete[] index_stack;
    }

    template <typename t>
    void array_based_bst<t>::traversal_inorder(size_t root, std::function<void(t& value)> const& completion) const {
        auto index_stack(new size_t[this->_size]);
        long index_stack_cursor(-1);
        size_t current_index(0);

        while (index_stack_cursor >= 0 || current_index < this->_size) {
            if (this->is_exist(current_index)) { // 현재 인덱스가 가르키고 있는 대상 유효할 경우(우선적으로 왼쪽 노드로 이동하기 위한 조건)
                index_stack[++index_stack_cursor] = current_index;
                current_index = this->get_child_index(current_index, direction::left); // 왼쪽 자식의 인덱스 이동

            } else {
                current_index = index_stack[index_stack_cursor--]; // 적재된 왼쪽 노드의 인덱스 정보를 꺼냄

                completion(this->_tree[current_index]);

                current_index = this->get_child_index(current_index, direction::right); // 오른쪽 자식 인덱스 이동
            }
        }

        delete[] index_stack;
    }

    template <typename t>
    void array_based_bst<t>::traversal_postorder(size_t root, std::function<void(t& value)> const& completion) const {
        auto visited_stack(new bool[this->_size]); // 방문 사실을 기록하는 스택
        auto index_stack(new size_t[this->_size]);
        long stack_cursor(0);
        visited_stack[stack_cursor] = false;
        index_stack[stack_cursor] = 0;

        while (stack_cursor >= 0) {
            auto is_visited(visited_stack[stack_cursor]);
            auto current_index(index_stack[stack_cursor]);
            --stack_cursor;

            if (!this->is_exist(current_index)) { // 유효하지 않은 노드 인덱스를 가르키는 경우
                continue;
            }

            if (is_visited) { // 이미 방문한 노드인 경우
                completion(this->_tree[current_index]); // 왼쪽 및 오른쪽 자식 노드를 모두 방문한 부모 노드이므로 해당 인덱스를 방문

            } else {
                index_stack[++stack_cursor] = current_index; // 아직 모든 자식 노드에 대해 방문하지 않은 노드이므로 다시 적재
                auto right_child_index(this->get_child_index(current_index, direction::right));
                auto left_child_index(this->get_child_index(current_index, direction::left));

                if (right_child_index < this->_size) {
                    index_stack[++stack_cursor] = right_child_index;
                    visited_stack[stack_cursor] = false; // 적재된 노드의 인덱스의 자식이 아직 방문되지 않았음을 표시
                }

                if (left_child_index < this->_size) {
                    index_stack[++stack_cursor] = left_child_index;
                    visited_stack[stack_cursor] = false;
                }
            }
        }

        delete[] visited_stack;
        delete[] index_stack;
    }

    template <typename t>
    void array_based_bst<t>::insert(t const& value) {
        this->search(value, [this, &value](size_t parent, size_t current, direction direction) {
            if (current == 0) { // 루트 노드의 인덱스 값이 초기값인 경우
                this->_tree[current] = value;

                return;
            }

            if (current >= this->_size) { // 새로운 노드 인덱스를 가르키는 경우
                this->resize(current * 2); // level 1의 크기만큼 만큼 확장
            }

            if (this->_tree[current] == t()) {
                this->_tree[current] = value;
            }
        });
    }

    template <typename t>
    void array_based_bst<t>::remove(t const& value) {
        this->search(value, [this, &value](size_t parent, size_t current, direction direction) {
            if (value == this->_tree[current]) { // 트리에서 해당하는 값의 노드 인덱스를 찾아낸 경우
                auto left_child_index(this->get_child_index(current, direction::left));
                auto right_child_index(this->get_child_index(current, direction::right));

                if (this->is_exist(left_child_index) && this->is_exist(right_child_index)) { // 양쪽 자식 노드 인덱스 모두 유효한 경우
                    auto successor_index(this->search_extrema(right_child_index, extrema::min)); // 오른쪽 자식 노드 인덱스의 최소 노드 인덱스
                    this->_tree[current] = this->_tree[successor_index]; // 계승 노드의 값을 제거할 노드에 복사
                    auto successor_right_child_index(this->get_child_index(successor_index, direction::right)); // 계승 노드 인덱스의 오른쪽 자식이 있는지 확인
                    this->_tree[successor_index] = this->is_exist(successor_right_child_index) ? this->_tree[successor_right_child_index] : t(); // 계승 노드의 오른쪽 자식이 있는 경우 해당 값을, 아닌 경우 기본 값을 계승 노드(최소값 노드)에 복사

                } else { // 리프 노드 인덱스이거나 자식이 하나인 경우
                    this->remove_at(current);
                }
            }
        });
    }

    // 연결 리스트 기반 이진 탐색 트리 구현
    template <typename t>
    linked_list_based_bst<t>::linked_list_based_bst() {

    }

    template <typename t>
    linked_list_based_bst<t>::linked_list_based_bst(std::initializer_list<t> list) {

    }

    template <typename t>
    linked_list_based_bst<t>::linked_list_based_bst(size_t size, t const& value) {

    }

    template <typename t>
    linked_list_based_bst<t>::linked_list_based_bst(size_t size) {

    }

    template <typename t>
    linked_list_based_bst<t>::~linked_list_based_bst() {

    }

    template <typename t>
    void linked_list_based_bst<t>::search(t const& value, std::function<void(node* parent, node* current, direction direction)> const& completion) const {
        node* parent;
        node* current(this->_root);
        bool is_left;

        while (current) {
            parent = current;

            if (value < current->_value) { // 현재 노드의 값이 삽입하려는 값보다 작은 경우
                current = current->_left; // 왼쪽 자식 노드로 이동
                is_left = true;

            } else if (value > current->_value) { // 현재 노드의 값이 삽입하려는 값보다 큰 경우
                current = current->_right; // 오른쪽 자식 노드로 이동
                is_left = false;

            } else { // 삽입하려는 값과 같은 값이 트리에 있는 경우
                break;
            }
        }
    }

    template <typename t>
    linked_list_based_bst<t>::node* linked_list_based_bst<t>::search_extrema(node* root, extrema extrema) const {

    }

    template <typename t>
    void linked_list_based_bst<t>::traversal_preorder(node* root, std::function<void(t& value)> const& completion) const {

    }

    template <typename t>
    void linked_list_based_bst<t>::traversal_inorder(node* root, std::function<void(t& value)> const& completion) const {

    }

    template <typename t>
    void linked_list_based_bst<t>::traversal_postorder(node* root, std::function<void(t& value)> const& completion) const {

    }

    template <typename t>
    void linked_list_based_bst<t>::insert(t const& value) {

    }

    template <typename t>
    void linked_list_based_bst<t>::remove(t const& value) {

    }









//    template <typename t>
//    binary_search_tree<t>::binary_search_tree():
//    _root(nullptr),
//    _size(0) {}
//
//    template <typename t>
//    binary_search_tree<t>::binary_search_tree(std::initializer_list<t> list) : binary_search_tree() {
//        for (auto const& value : list) {
//            this->insert(value);
//        }
//    }
//
//    template <typename t>
//    binary_search_tree<t>::binary_search_tree(size_t size, t const& value) : binary_search_tree() {
//        for (int i(0); i < size; i++) {
//            this->insert(value);
//        }
//    }
//
//    template <typename t>
//    binary_search_tree<t>::binary_search_tree(size_t size) : binary_search_tree(size, t()) {}
//
//    template <typename t>
//    binary_search_tree<t>::~binary_search_tree() {
//        this->traversal_postorder(this->_root, [](node* target) {
//            delete target;
//        });
//    }
//
//    template <typename t>
//    void binary_search_tree<t>::search(t const& value, std::function<void(node*, node*, bool)> completion) {
//        node* parent;
//        auto current(this->_root);
//        bool is_left(false);
//
//        while (current && current->_value != value) {
//            parent = current;
//
//            if (value < current->_value) {
//                is_left = true;
//                current = current->_left;
//
//            } else if (value > current->_value) {
//                is_left = false;
//                current = current->_right;
//            }
//        }
//
//        completion(parent, current, is_left);
//    }
//
//    template <typename t>
//    void binary_search_tree<t>::insert(t const& value) {
//        auto new_node(new node(value));
//
//        if (this->_root == nullptr) {
//            this->_root = new_node;
//
//            return;
//        }
//
//        this->search(value, [this, &new_node](node* parent, node* current, bool is_left) {
//            if (parent && current == nullptr) { // leaf 노드에 도달한 경우
//                if (is_left) {
//                    parent->_left = new_node;
//
//                } else {
//                    parent->_right = new_node;
//                }
//
//                ++this->_size;
//
//            } else { // 동일한 값을 가진 노드를 발견한 경우
//                delete new_node;
//            }
//        });
//    }
//
//    template <typename t>
//    void binary_search_tree<t>::remove(t const& value) {
//        if (this->_root == nullptr) {
//            return;
//        }
//
//        this->search(value, [this](node* parent, node* current, bool is_left) {
//            if (parent && current) {
//                node* replace_node;
//
//                if (current->_left == nullptr || current->_right == nullptr) { // 대상 노드의 자식이 1개만 있는 경우
//                    replace_node = current->_left ? : current->_right;
//
//                } else if (current->_left && current->_right) { // 대상 노드의 자식 노드가 둘 다 있는 경우
//                    auto successor_parent(current);
//                    auto successor(current->_right);
//
//                    while (successor->_left) { // 오른쪽 노드의 자식 중에 최소 값을 가진 노드 탐색(왼쪽 자식 노드가 없는 노드)
//                        successor_parent = successor;
//                        successor = successor->_left;
//                    }
//
//                    if (current->_right == successor) { // 최소 노드가 인접해 있는 경우
//                        successor->_left = current->_left;
//
//                    } else {
//                        successor_parent->_left = successor->_right; // 최소 노드에 오른쪽 자식 노드가 있는 경우 부모 노드와 연결, 아니면 nullptr 대입
//                        successor->_left = current->_left;
//                        successor->_right = current->_right;
//                    }
//
//                    replace_node = successor;
//                }
//
//                if (is_left) {
//                    parent->_left = replace_node;
//
//                } else {
//                    parent->_right = replace_node;
//                }
//
//                delete current;
//                --this->_size;
//            }
//        });
//    }
}