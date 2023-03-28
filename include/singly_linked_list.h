//
// Created by aircuve on 2023-03-23.
//

#pragma once
#include <iostream>
#include <memory>

namespace tk {
    template<typename t>
    class singly_linked_list {
    private:
        template <typename nt>
        struct node {
            nt _value;
            std::unique_ptr<node<nt>> _next;

            explicit node(const nt& value) :
            _value(value),
            _next(nullptr) {}
            node() : node(nt()) {}
        };

    private:
        std::unique_ptr<node<t>> _before_front;
        size_t _count;

    public:
        template <typename it>
        class iterator {
        private:
            node<it>* _cursor;

        public:
            using pointer_type = node<it>*;
            using reference_type = it&;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

            explicit iterator(pointer_type cursor) : _cursor(cursor) {}
            reference_type operator*();
            pointer_type operator->() { return this->_cursor; }
            iterator operator+(size_t index);
            iterator& operator++();
            iterator operator++(it);
            bool operator==(const iterator& other) const { return this->_cursor == other._cursor; }
            bool operator!=(const iterator& other) const { return this->_cursor != other._cursor; }
        };

    public:
        using iterator_type = iterator<t>;
        using const_iterator_type = iterator<const t>;

        explicit singly_linked_list() :
        _before_front(std::make_unique<node<t>>()),
        _count(0) {}
        ~singly_linked_list() = default;
        void push_front(const t& value);
        void pop_front();
        void assign(iterator_type iterator, const t& value);
        void insert_after(const_iterator_type iterator, const t& value);
        void remove_after(const_iterator_type iterator);
        t front() const { return this->_before_front->_next ? this->_before_front->_next->_value : t(); }
        size_t count() const { return this->_count; }
        const_iterator_type before_begin() const { return iterator<const t>(this->_before_front.get()); }
        iterator_type begin() const { return iterator<t>(this->_before_front->_next.get()); }
        iterator_type end() const { return iterator<t>(nullptr); }
    };
}