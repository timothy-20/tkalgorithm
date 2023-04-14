//
// Created by 임정운 on 2023/04/10.
//

#include <binary_search_tree.h>

namespace tk {
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
    size_t array_based_bst<t>::get_parent_index(size_t index) const {
        return (index - (index % 2 == 1 ? 1 : 2)) / 2;
    }

    template <typename t>
    size_t array_based_bst<t>::get_child_index(size_t index, bool is_left) const {
        return 2 * index + (is_left ? 1 : 2);
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
    void array_based_bst<t>::search(t const& value, std::function<void(size_t parent, size_t current, bool is_left)> const& completion) const {
        if (this->_tree[0] == t()) {
            completion(0, 0, true);

            return;
        }

        size_t parent_index(0);
        size_t current_index(0);
        bool is_left(false);

        while (current_index < this->_size) { // 트리의 크기를 넘지 않을 때까지 순회
            if (this->_tree[current_index] == value) { // 값에 해당하는 노드 인덱스에 도달한 경우
                break;
            }

            parent_index = current_index;
            is_left = this->_tree[parent_index] > value; // 값이 순회 도중의 노드 인덱스의 값보다 작은 경우 왼쪽, 큰 경우 오른쪽으로 설정
            current_index = this->get_child_index(parent_index, is_left);
        }

        completion(parent_index, current_index, is_left);
    }

    template <typename t>
    size_t array_based_bst<t>::search_edge(size_t root, bool is_min) const {
        if (root >= this->_size) {
            return 0;
        }

        auto current_index(root);

        do {
            current_index = this->get_child_index(current_index, is_min);
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

            if (current_index >= this->_size || this->_tree[current_index] == t()) {
                continue;
            }

            completion(this->_tree[current_index]);

            auto right_child_index(this->get_child_index(current_index, false));
            auto left_child_index(this->get_child_index(current_index, true));

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
            if (current_index < this->_size && this->_tree[current_index] != t()) { // 현재 인덱스가 가르키고 있는 대상 유효할 경우(우선적으로 왼쪽 노드로 이동하기 위한 조건)
                index_stack[++index_stack_cursor] = current_index;
                current_index = this->get_child_index(current_index, true); // 왼쪽 자식의 인덱스 이동

            } else {
                current_index = index_stack[index_stack_cursor--]; // 적재된 왼쪽 노드의 인덱스 정보를 꺼냄

                completion(this->_tree[current_index]);

                current_index = this->get_child_index(current_index, false); // 오른쪽 자식 인덱스 이동
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

            if (current_index >= this->_size || this->_tree[current_index] == t()) { // 인덱스가 최대 범위를 벗어났거나, 값이 유효하지 않은 경우
                continue;
            }

            if (is_visited) { // 이미 방문한 노드인 경우
                completion(this->_tree[current_index]); // 왼쪽 및 오른쪽 자식 노드를 모두 방문한 부모 노드이므로 해당 인덱스를 방문

            } else {
                index_stack[++stack_cursor] = current_index; // 아직 모든 자식 노드에 대해 방문하지 않은 노드이므로 다시 적재
                auto right_child_index(this->get_child_index(current_index, false));
                auto left_child_index(this->get_child_index(current_index, true));

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
        this->search(value, [this, &value](size_t parent, size_t current, bool is_left) {
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
        this->search(value, [this, &value](size_t parent, size_t current, bool is_left) {
            if (value == this->_tree[current]) { // 트리에서 해당하는 값의 노드 인덱스를 찾아낸 경우
                auto left_child_index(this->get_child_index(current, true));
                auto right_child_index(this->get_child_index(current, false));

                if ((left_child_index < this->_size && this->_tree[left_child_index] != t())
                ^ (right_child_index < this->_size && this->_tree[right_child_index] != t())) {

                }

                if ((left_child_index >= this->_size || this->_tree[left_child_index] == t())
                ^ (right_child_index >= this->_size || this->_tree[right_child_index] == t())) { // 한 개의 자식만 있는 노드 인덱스인 경우

                }
//                if ()
            }
        });
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
//    void binary_search_tree<t>::traversal_preorder(typename binary_search_tree<t>::node* root, std::function<void(node*)> completion) {
//        if (root == nullptr) {
//            return;
//        }
//
//        completion(root);
//        this->traversal_preorder(root->_left, completion);
//        this->traversal_preorder(root->_right, completion);
//    }
//
//    template <typename t>
//    void binary_search_tree<t>::traversal_inorder(typename binary_search_tree<t>::node* root, std::function<void(node*)> completion) {
//        if (root == nullptr) {
//            return;
//        }
//
//        this->traversal_inorder(root->_left, completion);
//        completion(root);
//        this->traversal_inorder(root->_right, completion);
//    }
//
//    template <typename t>
//    void binary_search_tree<t>::traversal_postorder(typename binary_search_tree<t>::node* root, std::function<void(node*)> completion) {
//        if (root == nullptr) {
//            return;
//        }
//
//        this->traversal_postorder(root->_left, completion);
//        this->traversal_postorder(root->_right, completion);
//        completion(root);
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
//
//    template class binary_search_tree<int>;
}