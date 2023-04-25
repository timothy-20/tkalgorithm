//
// Created by jungu on 4/22/2023.
//

#include <linked_list_based_bst.h>
#include <stack> // 구현을 위해 1차적으로 std 라이브러리 사용

namespace tk {
    // 연결 리스트 기반 이진 탐색 트리 구현
    template <typename t>
    linked_list_based_bst<t>::linked_list_based_bst() : _root(nullptr) {
    }

    // 값을 최대한 완전 이진 트리에 가깝께 구성하는 순서로 재조립하고 삽입을 수행하도록 구현
    // 이후 중복 값이 발생한 경우 해당 값을 제외하고 계속해서 삽입을 수행
    template <typename t>
    linked_list_based_bst<t>::linked_list_based_bst(std::initializer_list<t> list) : linked_list_based_bst() {
        // 삽입하는 값의 갯수가 홀수일 경우
        // 삽입하는 값의 갯수가 짝수일 경우

        for (t value : list) {

        }
    }

    template <typename t>
    linked_list_based_bst<t>::~linked_list_based_bst() {
        // in-order 순회를 이용하여 할당한 노드 포인터들을 해제
    }

    template <typename t>
    void linked_list_based_bst<t>::search(t const& value, std::function<void(node*& parent, node*& current, direction direction)> const& completion) const {
        if (!this->_root) {
            throw tk::null_pointer_access("Root node is nullptr in search.");
        }

        node* parent(nullptr);
        node* current(this->_root);
        auto direction(direction::none);

        while (current) {
            if (value == current->_value) { // 트리에서 동일한 값을 찾은 경우
                break;
            }

            parent = current;

            if (value < current->_value) { // 현재 노드의 값이 삽입하려는 값보다 작은 경우
                current = current->_left; // 왼쪽 자식 노드로 이동
                direction = direction::left;

            } else { // 현재 노드의 값이 삽입하려는 값보다 큰 경우
                current = current->_right; // 오른쪽 자식 노드로 이동
                direction = direction::right;
            }
        }

        completion(parent, current, direction);
    }

    template <typename t>
    typename linked_list_based_bst<t>::node* linked_list_based_bst<t>::search_extrema(node* root, extrema extrema) const {
        if (!root) {
            throw tk::null_pointer_access("Root node is nullptr in search extrema.");
        }

        node* parent(nullptr);

        while (root) {
            parent = root;

            switch (extrema) {
                case extrema::min: root = root->_left; break;
                case extrema::max: root = root->_right; break;
            }
        }

        return parent;
    }

    template <typename t>
    void linked_list_based_bst<t>::traversal_preorder(node* root, std::function<void(t& value)> const& completion) const {
        if (!root) {
            throw tk::null_pointer_access("Root node is nullptr in traversal pre-order");
        }

        std::stack<node*> node_stack;

        node_stack.push(root);

        while (!node_stack.empty()) {
            auto top_node(node_stack.top());

            node_stack.pop();
            completion(top_node->_value);

            // 스택이 LIFO(last in first out)로 동작하기 때문에 right를 먼저 삽입
            if (top_node->_right) {
                node_stack.push(top_node->_right);
            }

            if (top_node->_left) {
                node_stack.push(top_node->_left);
            }
        }
    }

    template <typename t>
    void linked_list_based_bst<t>::traversal_inorder(node* root, std::function<void(t& value)> const& completion) const {
        if (!root) {
            throw tk::null_pointer_access("Root node is nullptr in traversal in-order");
        }

        node* current(root);
        std::stack<node*> node_stack;

        while (current || !node_stack.empty()) {
            if (current) {
                node_stack.push(current);

                current = current->_left;

            } else {
                current = node_stack.top();

                node_stack.pop();
                completion(current->_value);

                current = current->_right;
            }
        }
    }

    template <typename t>
    void linked_list_based_bst<t>::traversal_postorder(node* root, std::function<void(t& value)> const& completion) const {
        if (!root) {
            throw tk::null_pointer_access("Root node is nullptr in traversal post-order");
        }

        std::stack<node*> node_stack_01, node_stack_02;

        node_stack_01.push(root);

        while (!node_stack_01.empty()) {
            auto current(node_stack_01.top());

            node_stack_01.pop();
            // 부모에 해당하는 노드가 가장 마지막에 쌓일 수 있도록 두 번째 스택에 저장
            node_stack_02.push(current);

            // 두 번째 stack에서 왼쪽 노드들이 아래에 쌓일 수 있도록 오른쪽보다 먼저 스택에 저장
            if (current->_left) {
                node_stack_01.push(current->_left);
            }

            if (current->_right) {
                node_stack_01.push(current->_right);
            }
        }

        // 이후 '왼쪽 - 오른쪽 - 부모' 의 순서로 노드가 삽입된 두 번째 스택을 순차적으로 순회
        while (!node_stack_02.empty()) {
            auto current(node_stack_02.top());

            node_stack_02.pop();
            completion(current->_value);
        }
    }

    template <typename t>
    void linked_list_based_bst<t>::insert(t const& value) {
        if (!this->_root) {
            this->_root = new node(value);

            return;
        }

        try {
            this->search(value, [value](node*& parent, node*& current, direction direction) {
                // 값이 트리에 포함되어 있지 않은 경우
                if (!current) {
                    auto new_node(new node(value));

                    switch (direction) {
                        case direction::left: parent->_left = new_node; break;
                        case direction::right: parent->_right = new_node; break;
                        case direction::none: return; // 루트 노드가 nullptr인 경우
                    }

                    // 부모 노드 설정
                    new_node->_parent = parent;
                }
            });

        } catch (std::exception const& e) {
            std::cerr << e.what() << '\n';
            throw tk::null_pointer_access("Occurred exception with insert.");
        }
    }

    template <typename t>
    void linked_list_based_bst<t>::remove(t const& value) {
        try {
            this->search(value, [this](node*& parent, node*& current, direction direction) {
                // 값이 트리에 포함되어 있는 경우
                if (current) {
                    if (current->_left && current->_right) { // 대상 노드의 자식이 2개 다 있는 경우
                        auto successor(this->search_extrema(current->_right, extrema::min)); // 대상 노드의 오른쪽 자식의 최소 값 노드를 가져옴
                        auto successor_right_child(successor->_right);
                        current->_value = successor->_value; // 계승 노드의 값을 삭제 대상 노드로 복사(변경)

                        if (successor_right_child) { // 계승 노드에 오른쪽 자식이 있는 경우
                            successor->_parent->_left = successor_right_child;
                            successor_right_child->_parent = successor->_parent;
                        }

                        delete successor;
                        successor = nullptr;

                    } else {
                        if (!current->_left ^ !current->_right) { // 대상 노드의 자식이 1개만 있는 경우
                            node* child_node(current->_left ? : current->_right);

                            switch (direction) {
                                case direction::left: parent->_left = child_node; break;
                                case direction::right: parent->_right = child_node; break;
                                default: break;
                            }

                            child_node->_parent = parent;
                        }

                        delete current;
                        current = nullptr;
                    }
                }
            });

        } catch (std::exception const& e) {
            std::cerr << e.what() << '\n';
            throw tk::null_pointer_access("Occurred exception with remove.");
        }
    }

    template <typename t>
    node<t>* linked_list_based_bst<t>::root() const {
        return this->_root;
    }

    template class binary_search_tree<int, node<int>*>;
    template class linked_list_based_bst<int>;
}