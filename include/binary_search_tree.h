//
// Created by 임정운 on 2023/04/04.
//

#pragma once
#include <iostream>
#include <algorithm>
#include <functional>

namespace tk {
    template <typename value_t, typename node_t>
    class binary_search_tree { // 이진 탐색 트리 인터페이스
    public:
        virtual void search(value_t const& value, std::function<void(node_t parent, node_t current, bool is_left)> const& completion) const = 0;
        virtual node_t search_edge(node_t root, bool is_min) const = 0;
        virtual void traversal_preorder(node_t root, std::function<void(value_t& value)> const& completion) const = 0;
        virtual void traversal_inorder(node_t root, std::function<void(value_t& value)> const& completion) const = 0;
        virtual void traversal_postorder(node_t root, std::function<void(value_t& value)> const& completion) const = 0;
        virtual void insert(value_t const& value) = 0;
        virtual void remove(value_t const& value) = 0;
    };

    template <typename t>
    class array_based_bst : public binary_search_tree<t, size_t> {
    private:
        size_t _size;
        t* _tree;

    private:
        size_t get_parent_index(size_t index) const;
        size_t get_child_index(size_t index, bool is_left) const;
        bool is_exist(size_t index) const;
        void resize(size_t new_size);

    public:
        explicit array_based_bst(size_t size = 14); // level 3 까지는 기본적으로 할당
        ~array_based_bst();
        void search(t const& value, std::function<void(size_t parent, size_t current, bool is_left)> const& completion) const override;
        size_t search_edge(size_t root, bool is_min) const override;
        void traversal_preorder(size_t root, std::function<void(t& value)> const& completion) const override;
        void traversal_inorder(size_t root, std::function<void(t& value)> const& completion) const override;
        void traversal_postorder(size_t root, std::function<void(t& value)> const& completion) const override;
        void insert(t const& value) override;
        void remove(t const& value) override;
    };

    template <typename t>
    struct node;

    template <typename t>
    class linked_list_based_bst : binary_search_tree<t, node<t>*> {
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
//        linked_list_based_bst();
//        linked_list_based_bst(std::initializer_list<t> list);
//        explicit linked_list_based_bst(size_t size, t const& value);
//        explicit linked_list_based_bst(size_t size);
//        ~linked_list_based_bst();
//        void insert(t const& value);
//        void remove(t const& value);
    };

    template class binary_search_tree<int, size_t>;
    template class binary_search_tree<int, node<int>*>;
    template class array_based_bst<int>;
    template class linked_list_based_bst<int>;
}