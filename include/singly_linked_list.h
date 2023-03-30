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
        struct node {
            t _value;
            std::unique_ptr<node> _next;

            explicit node(t const& value) :
            _value(value),
            _next(nullptr) {}
            node() : node(t()) {}
        };

    private:
        std::unique_ptr<node> _before_front;
        node* _back;
        size_t _count;

    public:
        template <typename it>
        class iterator {
            friend class singly_linked_list<t>;

        private:
            node* _cursor;

        public:
            using value_type = it;
            using pointer = it*;
            using reference = it&;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

            explicit iterator(node* cursor) : _cursor(cursor) {}
            reference operator*();
            pointer operator->();
            iterator& operator++();
            iterator operator++(value_type);
            bool operator==(iterator const& other) const { return this->_cursor == other._cursor; }
            bool operator!=(iterator const& other) const { return this->_cursor != other._cursor; }
        };

    public:
        using iterator_type = iterator<t>;
        using const_iterator_type = iterator<t const>;

        singly_linked_list(std::initializer_list<t> list);
        singly_linked_list(size_t count, t const& value);
        singly_linked_list(size_t count) : singly_linked_list(count, 0) {}
        singly_linked_list() : singly_linked_list(0) {}
        ~singly_linked_list() = default;
        void push_front(t const& value);
        void pop_front();
        void insert_after(const_iterator_type iterator, t const& value);
        void remove_after(const_iterator_type iterator);
        void assign(iterator_type iterator, t const& value);
        void resize(size_t size, t const& value = t());
        t front() const { return this->_before_front->_next ? this->_before_front->_next->_value : t(); }
        size_t count() const { return this->_count; }
        const_iterator_type before_begin() const { return iterator<t const>(this->_before_front.get()); }
        iterator_type begin() const { return iterator<t>(this->_before_front->_next.get()); }
        const_iterator_type cbegin() const { return iterator<t const>(this->_before_front->_next.get()); }
        iterator_type end() const { return iterator<t>(nullptr); }
        const_iterator_type cend() const { return iterator<t const>(nullptr); }
    };
}