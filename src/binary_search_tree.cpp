//
// Created by 임정운 on 2023/04/10.
//

#include <binary_search_tree.h>

namespace tk {
    template <typename t>
    binary_search_tree<t>::binary_search_tree():
    _root(nullptr),
    _size(0) {}

    template <typename t>
    binary_search_tree<t>::binary_search_tree(std::initializer_list<t> list) : binary_search_tree() {
        for (auto const& value : list) {
            this->insert(value);
        }
    }

    template <typename t>
    binary_search_tree<t>::binary_search_tree(size_t size, t const& value) : binary_search_tree() {
        for (int i(0); i < size; i++) {
            this->insert(value);
        }
    }

    template <typename t>
    binary_search_tree<t>::binary_search_tree(size_t size) : binary_search_tree(size, t()) {}

    template <typename t>
    binary_search_tree<t>::~binary_search_tree() {
        this->traversal_postorder(this->_root, [](node* target) {
            delete target;
        });
    }

    template <typename t>
    void binary_search_tree<t>::search(t const& value, std::function<void(node*, node*, bool)> completion) {
        node* parent;
        auto current(this->_root);
        bool is_left(false);

        while (current && current->_value != value) {
            parent = current;

            if (value < current->_value) {
                is_left = true;
                current = current->_left;

            } else if (value > current->_value) {
                is_left = false;
                current = current->_right;
            }
        }

        completion(parent, current, is_left);
    }

    template <typename t>
    void binary_search_tree<t>::traversal_preorder(typename binary_search_tree<t>::node* root, std::function<void(node*)> completion) {
        if (root == nullptr) {
            return;
        }

        completion(root);
        this->traversal_preorder(root->_left, completion);
        this->traversal_preorder(root->_right, completion);
    }

    template <typename t>
    void binary_search_tree<t>::traversal_inorder(typename binary_search_tree<t>::node* root, std::function<void(node*)> completion) {
        if (root == nullptr) {
            return;
        }

        this->traversal_inorder(root->_left, completion);
        completion(root);
        this->traversal_inorder(root->_right, completion);
    }

    template <typename t>
    void binary_search_tree<t>::traversal_postorder(typename binary_search_tree<t>::node* root, std::function<void(node*)> completion) {
        if (root == nullptr) {
            return;
        }

        this->traversal_postorder(root->_left, completion);
        this->traversal_postorder(root->_right, completion);
        completion(root);
    }

    template <typename t>
    void binary_search_tree<t>::insert(t const& value) {
        auto new_node(new node(value));

        if (this->_root == nullptr) {
            this->_root = new_node;

            return;
        }

        this->search(value, [this, &new_node](node* parent, node* current, bool is_left) {
            if (parent && current == nullptr) { // leaf 노드에 도달한 경우
                if (is_left) {
                    parent->_left = new_node;

                } else {
                    parent->_right = new_node;
                }

                ++this->_size;

            } else { // 동일한 값을 가진 노드를 발견한 경우
                delete new_node;
            }
        });
    }

    template <typename t>
    void binary_search_tree<t>::remove(t const& value) {
        if (this->_root == nullptr) {
            return;
        }

        this->search(value, [this](node* parent, node* current, bool is_left) {
            if (parent && current) {
                node* replace_node;

                if (current->_left == nullptr || current->_right == nullptr) { // 대상 노드의 자식이 1개만 있는 경우
                    replace_node = current->_left ? : current->_right;

                } else if (current->_left && current->_right) { // 대상 노드의 자식 노드가 둘 다 있는 경우
                    auto successor_parent(current);
                    auto successor(current->_right);

                    while (successor->_left) { // 오른쪽 노드의 자식 중에 최소 값을 가진 노드 탐색(왼쪽 자식 노드가 없는 노드)
                        successor_parent = successor;
                        successor = successor->_left;
                    }

                    if (current->_right == successor) { // 최소 노드가 인접해 있는 경우
                        successor->_left = current->_left;

                    } else {
                        successor_parent->_left = successor->_right; // 최소 노드에 오른쪽 자식 노드가 있는 경우 부모 노드와 연결, 아니면 nullptr 대입
                        successor->_left = current->_left;
                        successor->_right = current->_right;
                    }

                    replace_node = successor;
                }

                if (is_left) {
                    parent->_left = replace_node;

                } else {
                    parent->_right = replace_node;
                }

                delete current;
                --this->_size;
            }
        });
    }

    template class binary_search_tree<int>;
}