//
// Created by 임정운 on 2023/04/04.
//

#pragma once
#include <iostream>
#include <algorithm>
#include <functional>

namespace tk {
    template <typename t>
    class binary_search_tree { // 이진 탐색 트리 인터페이스
    public:
        virtual void* search(t const& value) = 0;
        virtual void* traversal_preorder(void* root, std::function<void(void* target)> completion) const = 0;
        virtual void* traversal_inorder(void* root, std::function<void(void* target)> completion) const = 0;
        virtual void* traversal_postorder(void* root, std::function<void(void* target)> completion) const = 0;
        virtual void insert(t const& value) = 0;
        virtual void remove(t const& value) = 0;
    };

    template <typename t>
    class array_based_bst : public binary_search_tree<t> {
    private:
        size_t _size;
        t* _tree;

    private:
        size_t get_parent_index(size_t index) const {
            return (index - (index % 2 == 1 ? 1 : 2)) / 2;
        }
        size_t get_child_index(size_t index, bool is_left) const {
            return 2 * index + (is_left ? 1 : 2);
        }
        void resize(size_t new_size) {
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

    public:
        explicit array_based_bst(size_t size) :
        _size(size),
        _tree(new t[size]) {
            std::fill(this->_tree, this->_tree + this->_size, t());
        }
        ~array_based_bst() {
            delete[] this->_tree;
        }
        void insert(t const& value) override {
            if (this->_tree[0] == t()) {
                this->_tree[0] = value;

                return;
            }

            size_t index(0);

            while (true) {
                if (this->_tree[index] == value) { // 중복된 값이 존재하는 경우 삽입을 중단
                    return;
                }

                auto child_index(this->get_child_index(index, this->_tree[index] > value));

                if (this->_tree[child_index] == t()) {
                    this->_tree[child_index] = value;

                } else {
                    index = child_index;
                }
            }
        }
        void remove()
    };

    template <typename t>
    class linked_list_based_bst : binary_search_tree<t> {
//    private:
//        struct node {
//            t _value;
//            node* _left;
//            node* _right;
//
//            explicit node(t const& value) :
//                    _value(value),
//                    _left(nullptr),
//                    _right(nullptr) {}
//            node() : node(t()) {}
//        };
//
//    private:
//        size_t _size;
//        node* _root;
//
//    private:
//        void search(t const& value, std::function<void(node* parent, node* current, bool is_left)> completion);
//        void traversal_preorder(node* root, std::function<void(node* target)> completion);
//        void traversal_inorder(node* root, std::function<void(node* target)> completion);
//        void traversal_postorder(node* root, std::function<void(node* target)> completion);
//
//    public:
//        binary_search_tree();
//        binary_search_tree(std::initializer_list<t> list);
//        explicit binary_search_tree(size_t size, t const& value);
//        explicit binary_search_tree(size_t size);
//        ~binary_search_tree();
//        void insert(t const& value);
//        void remove(t const& value);
    };
}