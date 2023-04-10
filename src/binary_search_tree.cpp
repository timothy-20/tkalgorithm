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
    void binary_search_tree<t>::search(t const& value, std::function<void(node*, node*, bool, bool)> completion) {
        auto current(this->_root);
        node* parent;
        bool is_left(false);
        bool is_right(false);

        while (current && current->_value != value) {
            parent = current;

            if (value < current->_value) {
                is_left = true;
                is_right = false;
                current = current->_left;

            } else if (value > current->_value) {
                is_left = false;
                is_right = true;
                current = current->_right;
            }
        }

        completion(parent, current, is_left, is_right);
    }

    template <typename t>
    void binary_search_tree<t>::insert(t const& value) {
        auto new_node(new node(value));

        if (this->_root == nullptr) {
            this->_root = new_node;

            return;
        }

        this->search(value, [&new_node](node* parent, node* current, bool is_left, bool is_right) {
            if (current == nullptr) {
                if (is_left) {
                    parent->_left = new_node;

                } else if (is_right) {
                    parent->_right = new_node;

                } else {
                    delete new_node;
                }
            }
        });
    }
    //        auto new_node(new node(value));
//
//        if (this->_root == nullptr) {
//            this->_root = new_node;
//
//            return;
//        }
//
//        auto current(this->_root);
//        node* parent;
//
//        while(true) {
//            parent = current;
//
//            if (new_node->_value < current->_value) {
//                current = current->_left; // 경로에 있는 노드의 값보다 삽입하려는 값이 큰 경우 왼쪽으로 이동
//
//                if (current == nullptr) {
//                    parent->_left = new_node;
//
//                    return;
//                }
//
//            } else if (new_node->_value > current->_value) {
//                current = current->_right; // 경로에 있는 노드의 값보다 삽입하려는 값이 큰 경우 오른쪽으로 이동
//
//                if (current == nullptr) {
//                    parent->_right = new_node;
//
//                    return;
//                }
//
//            } else {
//                delete new_node; // tree에 있는 노드 중 같은 값을 가지고 있는 노드가 있다면 삽입을 취소
//
//                return;
//            }
//        }

    template <typename t>
    void binary_search_tree<t>::remove(t const& value) {

    }

    template class binary_search_tree<int>;
}