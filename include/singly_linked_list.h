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

            explicit node(const t& value) :
            _value(value),
            _next(nullptr) {}
            node() : node(t()) {}
        };

    private:
        std::unique_ptr<node> _front;
        size_t _count;

    public:
        class iterator {
        private:
            node* _cursor;

        public:
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

            explicit iterator(node* cursor) : _cursor(cursor) {}
            t& operator*();
            node* operator->() { return this->_cursor; }
            iterator operator+(size_t index);
            iterator& operator++();
            iterator operator++(t);
            bool operator==(const iterator& other) const { return this->_cursor == other._cursor; }
            bool operator!=(const iterator& other) const { return this->_cursor != other._cursor; }
        };

    public:
        explicit singly_linked_list() :
        _front(nullptr),
        _count(0) {}
        ~singly_linked_list() = default;
        void push_front(const t& value);
        void pop_front();
        void assign(iterator iterator, const t& value);
        void assign(size_t index, const t& value);
        void insert_after(iterator iterator, const t& value);
        void remove_after(iterator iterator);
        t front() const { return this->_front ? this->_front->_value : t(); }
        size_t count() const { return this->_count; }
        iterator begin() const { return iterator(this->_front.get()); }
        iterator end() const { return iterator(nullptr); }
    };
}