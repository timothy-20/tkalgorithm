//
// Created by 임정운 on 2023/04/04.
//

#pragma once
#include <iostream>
#include <algorithm>
#include <functional>

namespace tk {
    template <typename value_t, typename node_t>
    class binary_search_tree {
    public:
        class null_pointer_access : public std::exception {
        public:
            explicit null_pointer_access(char const* reason) : _reason(reason) {}
            virtual ~null_pointer_access() noexcept {}
            virtual char const* what() const noexcept override {
                return this->_reason;
            }

        private:
            char const* _reason;
        };

    public:
        enum class direction { none, left, right };
        enum class extrema { min, max };

    public:
        virtual void search(value_t const& value, std::function<void(node_t& parent, node_t& current, direction direction)> const& completion) const = 0;
        virtual node_t search_extrema(node_t root, extrema extrema) const = 0;
        virtual void traversal_preorder(node_t root, std::function<void(value_t& value)> const& completion) const = 0;
        virtual void traversal_inorder(node_t root, std::function<void(value_t& value)> const& completion) const = 0;
        virtual void traversal_postorder(node_t root, std::function<void(value_t& value)> const& completion) const = 0;
        virtual void insert(value_t const& value) = 0;
        virtual void remove(value_t const& value) = 0;
        virtual node_t root() const = 0;
    };
}