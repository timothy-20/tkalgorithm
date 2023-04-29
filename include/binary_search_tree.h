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

    // 가능한 사용자 정의 노드 타입에 대한 타입 트레잇
//    template <typename T, typename = void>
//    struct is_node_type : public std::false_type {};

    // 이진 탐색 트리 인터페이스
    template <typename value_t,
            typename node_t,
            typename std::enable_if_t<is_comparable<value_t>::value, int> = 0
            >
    class binary_search_tree {
    public:
        enum class direction { none, left, right };
        enum class extrema { min, max };

    public:
        virtual ~binary_search_tree() = default;
        // 요소 색인
        virtual void search(value_t const& value, std::function<void(node_t& parent, node_t& current, direction direction)> const& completion) const = 0;
        virtual node_t search_extrema(node_t root, extrema extrema) const = 0;
        // 요소 순회
        virtual void traversal_preorder(node_t root, std::function<void(value_t& value)> const& completion) const = 0;
        virtual void traversal_inorder(node_t root, std::function<void(value_t& value)> const& completion) const = 0;
        virtual void traversal_postorder(node_t root, std::function<void(value_t& value)> const& completion) const = 0;
        // 요소 수정
        virtual void insert(value_t const& value) = 0;
        virtual void remove(value_t const& value) = 0;
        // 요소 접근
        virtual node_t root() const = 0;
    };
}