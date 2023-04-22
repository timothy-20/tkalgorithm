//
// Created by jungu on 4/22/2023.
//

#pragma once

#include <binary_search_tree.h>

namespace tk {
    template <typename t>
    class array_list_based_bst : public binary_search_tree<t, size_t> {
    public:
        using direction = typename binary_search_tree<t, size_t>::direction;
        using extrema = typename binary_search_tree<t, size_t>::extrema;

        explicit array_list_based_bst(size_t size = 14); // level 3 까지는 기본적으로 할당
        ~array_list_based_bst();

        void search(t const& value, std::function<void(size_t& parent, size_t& current, direction direction)> const& completion) const override;
        size_t search_extrema(size_t root, extrema extrema) const override;
        void traversal_preorder(size_t root, std::function<void(t& value)> const& completion) const override;
        void traversal_inorder(size_t root, std::function<void(t& value)> const& completion) const override;
        void traversal_postorder(size_t root, std::function<void(t& value)> const& completion) const override;
        void insert(t const& value) override;
        void remove(t const& value) override;

    private:
        size_t _size;
        t* _tree;

    private:
        size_t get_child_index(size_t index, direction direction) const;
        bool is_exist(size_t index) const;
        void resize(size_t new_size);
        void remove_at(size_t index);
    };
}