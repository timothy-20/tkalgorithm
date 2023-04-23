//
// Created by jungu on 4/22/2023.
//

#include <linked_list_based_bst.h>
#include <stack> // 구현을 위해 1차적으로 std 라이브러리 사용

namespace tk {
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
    void linked_list_based_bst<t>::search(t const& value, std::function<void(node*& parent, node*& current, direction direction)> const& completion) const {
        if (!this->_root) {
            // 예외 발생

            return;
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
            // 예외 발생

            return nullptr;
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
            // 예외 발생

            return;
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
            // 예외 발생

            return;
        }

        std::stack<node*> node_stack;

        node_stack.push(root);

        while (!node_stack.empty()) {
            // 1. 최대한 왼쪽으로 이동하면서 노드를 스택에 채움
            // 2. 더 이상 왼쪽에 노드가 없는 경우 해당 노드를 출력
            // 3. 노드가 출력되는 상황에서 출력되는 노드에 오른쪽 노드가 있다면 이를 스택에 채움

            if (node_stack.top()->_left) {

                node_stack.push(node_stack.top()->_left);

            } else {
                auto top_node(node_stack.top());

                node_stack.pop();

                completion(top_node->_value);

                if (top_node->_right) {
                    node_stack.push(top_node->_right);
                }
            }
        }
    }

    template <typename t>
    void linked_list_based_bst<t>::traversal_postorder(node* root, std::function<void(t& value)> const& completion) const {
        if (!root) {
            // 예외 발생

            return;
        }
    }

    template <typename t>
    void linked_list_based_bst<t>::insert(t const& value) {
        if (!this->_root) {
            this->_root = new node(value);

            return;
        }

        this->search(value, [value](node*& parent, node*& current, direction direction) {
            if (!current) { // 값이 트리에 포함되어 있지 않은 경우
                auto new_node(new node(value));

                switch (direction) {
                    case direction::left: parent->_left = new_node; break;
                    case direction::right: parent->_right = new_node; break;
                    case direction::none: return; // 루트 노드가 nullptr인 경우
                }

                new_node->_parent = parent; // 부모 노드 설정
            }
        });
    }

    template <typename t>
    void linked_list_based_bst<t>::remove(t const& value) {
        // 예외 처리, search에서 root가 nullptr 일 경우 예외를 발생시키고 있으니 이를 전달하면 될 듯.

        this->search(value, [this](node*& parent, node*& current, direction direction) {
            if (current) { // 값이 트리에 포함되어 있는 경우
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
    }

    template <typename t>
    node<t>* linked_list_based_bst<t>::root() const {
        return this->_root;
    }

    template class binary_search_tree<int, node<int>*>;
    template class linked_list_based_bst<int>;
}