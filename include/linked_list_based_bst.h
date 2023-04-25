//
// Created by jungu on 4/22/2023.
//

#pragma once

#include <binary_search_tree.h>

namespace tk {
    template <typename nt>
    struct node {
        nt _value;
        node* _left;
        node* _right;
        node* _parent;

        explicit node(nt const& value) :
        _value(value),
        _left(nullptr),
        _right(nullptr),
        _parent(nullptr) {}
        node() : node(nt()) {}
    };

    template <typename t>
    class linked_list_based_bst : public binary_search_tree<t, tk::node<t>*> {
    public:
        using node = typename tk::node<t>;
        using direction = typename binary_search_tree<t, node*>::direction;
        using extrema = typename binary_search_tree<t, node*>::extrema;

        linked_list_based_bst();
        // 정렬 알고리즘 지원 함수 구현 후, 내부 기능 구현할 것
        // 사용자의 편의를 위해 제공되는 생성자 기능
        linked_list_based_bst(std::initializer_list<t> list);
        ~linked_list_based_bst();

        void search(t const& value, std::function<void(node*& parent, node*& current, direction direction)> const& completion) const override;
        node* search_extrema(node* root, extrema extrema) const override;
        void traversal_preorder(node* root, std::function<void(t& value)> const& completion) const override;
        void traversal_inorder(node* root, std::function<void(t& value)> const& completion) const override;
        void traversal_postorder(node* root, std::function<void(t& value)> const& completion) const override;
        void insert(t const& value) override;
        void remove(t const& value) override;
        node* root() const override;

    private:
        node* _root;
    };
}