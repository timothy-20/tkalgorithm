//
// Created by 임정운 on 2023/04/04.
//

#pragma once
#include <iostream>
#include <functional>

namespace tk {
    template <typename t>
    class binary_search_tree {
    private:
        struct node {
            t _value;
            node* _left;
            node* _right;

            explicit node(t const& value) :
            _value(value),
            _left(nullptr),
            _right(nullptr) {}
            node() : node(t()) {}
        };

    private:
        size_t _size;
        node* _root;

    private:
        void search(t const& value, std::function<void(node* parent, node* current, bool is_left)> completion);
        void traversal_preorder(node* root, std::function<void(node* target)> completion);
        void traversal_inorder(node* root, std::function<void(node* target)> completion);
        void traversal_postorder(node* root, std::function<void(node* target)> completion);

    public:
        binary_search_tree();
        binary_search_tree(std::initializer_list<t> list);
        explicit binary_search_tree(size_t size, t const& value);
        explicit binary_search_tree(size_t size);
        ~binary_search_tree();
        void insert(t const& value);
        void remove(t const& value);
    };
}