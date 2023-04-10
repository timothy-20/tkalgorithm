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

    }

    template <typename t>
    binary_search_tree<t>::binary_search_tree(size_t size, t const& value) : binary_search_tree() {

    }

    template <typename t>
    binary_search_tree<t>::binary_search_tree(size_t size) : binary_search_tree(size, t()) {}

    template <typename t>
    binary_search_tree<t>::~binary_search_tree() {

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
    typename binary_search_tree<t>::node* binary_search_tree<t>::search_min(typename binary_search_tree<t>::node* target_node) {
        if (target_node == nullptr) {
            return nullptr;
        }

        node* parent;
        auto current(target_node);

        return parent;
    }

    template <typename t>
    void binary_search_tree<t>::insert(t const& value) {
        auto new_node(new node(value));

        if (this->_root == nullptr) {
            this->_root = new_node;

            return;
        }

        this->search(value, [&new_node](node* parent, node* current, bool is_left) {
            if (parent && current == nullptr) { // leaf 노드에 도달한 경우
                if (is_left) {
                    parent->_left = new_node;

                } else {
                    parent->_right = new_node;
                }

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
                if (current->_left == nullptr && current->_right == nullptr) { // 대상 노드가 leaf 노드일 경우
                    if (is_left) {
                        parent->_left = nullptr;

                    } else {
                        parent->_right = nullptr;
                    }

                    delete current;

                } else if (current->_left == nullptr || current->_right == nullptr) { // 대상 노드의 자식이 1개만 있는 경우
                    auto child(current->_left ? : current->_right);

                    if (is_left) {
                        parent->_left = child;

                    } else {
                        parent->_right = child;
                    }

                    delete current;

                } else { // 대상 노드의 자식 노드가 둘 다 있는 경우

                }
            }
        });
    }

    template class binary_search_tree<int>;
}