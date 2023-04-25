//
// Created by jungu on 4/22/2023.
//

#include <array_list_based_bst.h>

namespace tk {
    // 배열 기반 이진 탐색 트리 구현
    template <typename t>
    array_list_based_bst<t>::array_list_based_bst(size_t size) :
    _size(size),
    _tree(new t[size]) {
        std::fill(this->_tree, this->_tree + this->_size, t());
    }

    template <typename t>
    array_list_based_bst<t>::array_list_based_bst(std::initializer_list<t> list) : array_list_based_bst(list.size()) {
        for (t value : list) {

        }
    }

    template <typename t>
    array_list_based_bst<t>::~array_list_based_bst() {
        delete[] this->_tree;
    }

    template <typename t>
    size_t array_list_based_bst<t>::get_child_index(size_t index, direction direction) const {
        switch (direction) {
            case direction::none: return index;
            case direction::left: return 2 * index + 1;
            case direction::right: return 2 * index + 2;
        }
    }

    template <typename t>
    bool array_list_based_bst<t>::is_exist(size_t index) const {
        return index < this->_size && this->_tree[index] != t();
    }

    template <typename t>
    void array_list_based_bst<t>::resize(size_t new_size) {
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
    void array_list_based_bst<t>::remove_at(size_t index) { // remove 함수에 대한 도우미 함수
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
    void array_list_based_bst<t>::search(t const& value, std::function<void(size_t& parent, size_t& current, direction direction)> const& completion) const {
        size_t parent_index(0);
        size_t current_index(0);
        auto direction(direction::none);

        if (this->_tree[0] == t()) {
            completion(parent_index, current_index, direction);

            return;
        }

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
    size_t array_list_based_bst<t>::search_extrema(size_t root, extrema extrema) const {
        if (!this->is_exist(root)) {
            return 0;
        }

        auto direction(extrema == extrema::min ? direction::left : direction::right);

        do {
            root = this->get_child_index(root, direction);
        } while (root < this->_size);

        return root;
    }

    template <typename t>
    void array_list_based_bst<t>::traversal_preorder(size_t root, std::function<void(t& value)> const& completion) const {
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
    void array_list_based_bst<t>::traversal_inorder(size_t root, std::function<void(t& value)> const& completion) const {
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
    void array_list_based_bst<t>::traversal_postorder(size_t root, std::function<void(t& value)> const& completion) const {
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
    void array_list_based_bst<t>::insert(t const& value) {
        this->search(value, [this, &value](size_t& parent, size_t& current, direction direction) {
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
    void array_list_based_bst<t>::remove(t const& value) {
        this->search(value, [this, &value](size_t& parent, size_t& current, direction direction) {
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

    template <typename t>
    size_t array_list_based_bst<t>::root() const {
        return 0;
    }

    template class binary_search_tree<int, size_t>;
    template class array_list_based_bst<int>;
}
