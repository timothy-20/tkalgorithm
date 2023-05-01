//
// Created by 임정운 on 2023/04/04.
//

#pragma once
#include <iostream>
#include <algorithm>
#include <functional>
#include <type_traits>

// 구현 시 참고할 만한 구현체들
// c++의 std::set(https://en.cppreference.com/w/cpp/container/set)
// objective c의 NSSet(https://developer.apple.com/documentation/foundation/nsset?language=objc)

namespace tk {
    // 비교 가능 대상에 대한 타입 트레잇
    template <typename T, typename = void>
    struct is_comparable : public std::false_type {};

    template <typename T>
    struct is_comparable<T, std::enable_if_t<
            std::is_same_v<decltype(std::declval<T>() < std::declval<T>()), bool>
            && std::is_same_v<decltype(std::declval<T>() <= std::declval<T>()), bool>
            && std::is_same_v<decltype(std::declval<T>() > std::declval<T>()), bool>
            && std::is_same_v<decltype(std::declval<T>() >= std::declval<T>()), bool>
            && std::is_same_v<decltype(std::declval<T>() == std::declval<T>()), bool>>
            > : public std::true_type {};

    // 이진 탐색 트리 인터페이스
    template <typename Value_t,
            typename Node_t,
            typename std::enable_if_t<is_comparable<Value_t>::value, int> = 0>
    class binary_search_tree {
    public:
        enum class direction { none, left, right };
        enum class extrema { min, max };

    public:
        virtual ~binary_search_tree() = default;
        virtual void insert(Value_t const& value) = 0;
        virtual void remove(Value_t const& value) = 0;
        // 유틸리티 용도의 탐색 함수.

    protected:
        virtual void search(Value_t const& value, std::function<void(Node_t& parent, Node_t& current, direction direction)> const& completion) const = 0;
        virtual Node_t search_extrema(Node_t root, extrema extrema) const = 0;
        virtual void traversal_preorder(Node_t root, std::function<void(Node_t& current)> const& completion) const = 0;
        virtual void traversal_inorder(Node_t root, std::function<void(Node_t& current)> const& completion) const = 0;
        virtual void traversal_postorder(Node_t root, std::function<void(Node_t& current)> const& completion) const = 0;
        virtual Node_t root() const = 0;
    };
}