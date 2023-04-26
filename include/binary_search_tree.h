//
// Created by 임정운 on 2023/04/04.
//

#pragma once
#include <iostream>
#include <algorithm>
#include <functional>

// 구현 시 참고할 만한 구현체들
// c++의 std::set(https://en.cppreference.com/w/cpp/container/set)
// objective c의 NSSet(https://developer.apple.com/documentation/foundation/nsset?language=objc)

namespace tk {
    template <typename t>
    class binary_search_tree_exception : public std::exception {
    public:
        explicit binary_search_tree_exception(char const* reason) : _reason(reason) {
        }
        ~binary_search_tree_exception() override = default;
        const char * what() const noexcept override {
            return this->_reason;
        }

    private:
        char const* _reason;
    };

    // nullptr인 노드에 접근했을 경우 발생하는 예외
    class null_pointer_access : public binary_search_tree_exception<null_pointer_access> {
    public:
        using binary_search_tree_exception::binary_search_tree_exception;
    };

    template <typename value_t, typename node_t>
    class binary_search_tree {
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