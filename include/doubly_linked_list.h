//
// Created by aircuve on 2023-03-27.
//

#pragma once
#include <iostream>
#include <memory>

namespace tk {
    template <typename t>
    class doubly_linked_list {
    private:
        struct node {
            std::shared_ptr<node> _prev;
            std::shared_ptr<node> _next;
            t _value;
            bool _is_enable;

            explicit node(t const& value, bool is_enable) :
            _prev(nullptr),
            _next(nullptr),
            _value(value),
            _is_enable(is_enable) {}
            node() : node(t(), true) {}
        };

    private:
        std::shared_ptr<node> _before_front;
        std::shared_ptr<node> _after_back;
        size_t _count;

    public:
        template <typename it>
        class iterator {
            friend class doubly_linked_list<t>;

        private:
            std::shared_ptr<node> _cursor;

        public:
            using value_type = it;
            using pointer = it*;
            using reference = it&;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::bidirectional_iterator_tag;

            explicit iterator(std::shared_ptr<node> cursor) : _cursor(cursor) {}
            reference operator*();
            pointer operator->();
            virtual iterator& operator++();
            virtual iterator operator++(value_type);
            virtual iterator& operator--();
            virtual iterator operator--(value_type);
            bool operator==(iterator const& other) const { return this->_cursor == other._cursor; }
            bool operator!=(iterator const& other) const { return this->_cursor != other._cursor; }
        };

        template <typename rit>
        class reverse_iterator : public iterator<rit> {
        public:
            reverse_iterator(const iterator<rit>& base) : iterator<rit>(base) {}
            iterator<rit>& operator++() override;
            iterator<rit> operator++(typename iterator<rit>::value_type) override;
            iterator<rit>& operator--() override;
            iterator<rit> operator--(typename iterator<rit>::value_type) override;
        };

    public:
        using iterator_type = iterator<t>;
        using const_iterator_type = iterator<t const>;
        using reverse_iterator_type = reverse_iterator<t>;
        using const_reverse_iterator_type = reverse_iterator<t const>;

        doubly_linked_list(std::initializer_list<t> list) :
        _before_front(std::make_shared<node>(t(), false)),
        _after_back(std::make_shared<node>(t(), false)),
        _count(0) {
            for (auto const& value : list) {
                this->push_back(value);
            }
        }
        doubly_linked_list(size_t count, t const& value) :
        _before_front(std::make_shared<node>(t(), false)),
        _after_back(std::make_shared<node>(t(), false)),
        _count(0) {
            for (int i(0); i < count; i++) {
                this->push_back(value);
            }
        }
        doubly_linked_list(size_t count) : doubly_linked_list(count, 0) {}
        doubly_linked_list() : doubly_linked_list(0) {}
        ~doubly_linked_list() = default;
        void push_front(t const& value);
        void pop_front();
        void push_back(t const& value);
        void pop_back();
        void insert(const_iterator_type iterator, t const& value);
        void remove(const_iterator_type iterator);
        void assign(iterator_type iterator, t const& value);
        size_t count() const { return this->_count; }
        t front() const { return this->_before_front->_next ? this->_before_front->_next->_value : t(); }
        t back() const { return this->_after_back->_prev ? this->_after_back->_prev->_value : t(); }
        iterator_type begin() const { return iterator<t>(this->_before_front->_next); }
        const_iterator_type cbegin() const { return iterator<t const>(this->_before_front->_next); }
        reverse_iterator_type rbegin() const { return iterator<t>(this->_after_back->_prev); }
        const_reverse_iterator_type crbegin() const { return iterator<t const>(this->_after_back->_prev); }
        iterator_type end() const { return iterator<t>(this->_after_back); }
        const_iterator_type cend() const { return iterator<t const>(this->_after_back); }
        reverse_iterator_type rend() const { return iterator<t>(this->_before_front); }
        const_reverse_iterator_type crend() const { return iterator<t const>(this->_before_front); }
    };
}