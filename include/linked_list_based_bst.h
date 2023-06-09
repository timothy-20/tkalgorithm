//
// Created by jungu on 4/22/2023.
//

#pragma once
#include <binary_search_tree.h>

namespace tk {
    template <typename nt>
    struct node {
        nt value;
        node* left;
        node* right;
        node* parent;

        explicit node(nt const& value) :
        value(value),
        left(nullptr),
        right(nullptr),
        parent(nullptr) {}
        node() : node(nt()) {}
    };

    template <typename t>
    class linked_list_based_bst : public binary_search_tree<t, tk::node<t>*> {
    public:
        using node = typename tk::node<t>;
        using direction = typename binary_search_tree<t, node*>::direction;
        using extrema = typename binary_search_tree<t, node*>::extrema;

        linked_list_based_bst();
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