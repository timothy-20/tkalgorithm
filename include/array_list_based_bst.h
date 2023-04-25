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

        // level 3 까지는 기본적으로 할당
        explicit array_list_based_bst(size_t size = 14);
        // 정렬 알고리즘 지원 함수 구현 후, 내부 기능 구현할 것
        // 사용자의 편의를 위해 제공되는 생성자 기능
        array_list_based_bst(std::initializer_list<t> list);
        ~array_list_based_bst();

        void search(t const& value, std::function<void(size_t& parent, size_t& current, direction direction)> const& completion) const override;
        size_t search_extrema(size_t root, extrema extrema) const override;
        void traversal_preorder(size_t root, std::function<void(t& value)> const& completion) const override;
        void traversal_inorder(size_t root, std::function<void(t& value)> const& completion) const override;
        void traversal_postorder(size_t root, std::function<void(t& value)> const& completion) const override;
        void insert(t const& value) override;
        void remove(t const& value) override;
        size_t root() const override;

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