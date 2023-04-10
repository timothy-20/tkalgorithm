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
    void binary_search_tree<t>::insert(t const& value) {
        auto new_node(new node(value));

        if (this->_root == nullptr) {
            this->_root = new_node;

            return;
        }

        this->search(value, [&new_node](node* parent, node* current, bool is_left) {
            if (parent && current == nullptr) {
                if (is_left) {
                    parent->_left = new_node;

                } else {
                    parent->_right = new_node;
                }

            } else {
                delete new_node;
            }
        });
    }

    template <typename t>
    void binary_search_tree<t>::remove(t const& value) {
        if (this->_root == nullptr) {
            return;
        }

        this->search(value, [](node* parent, node* current, bool is_left) {
            if (parent && current) {
                if (is_left) {

                } else {

                }
            }
        });
    }

    template class binary_search_tree<int>;
}