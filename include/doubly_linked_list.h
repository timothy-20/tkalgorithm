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

            explicit node(t const& value) :
            _prev(nullptr),
            _next(nullptr),
            _value(value) {}
            node() : node(t()) {}
        };

    private:
        std::shared_ptr<node> _front;
        std::shared_ptr<node> _back;
        size_t _count;

    public:
        template <typename it>
        class iterator {
            friend class doubly_linked_list<t>;

        private:
            std::shared_ptr<node> _cursor;

        public:
            using value_type = it;
            using pointer_type = it*;
            using reference_type = it&;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::bidirectional_iterator_tag;

            explicit iterator(std::shared_ptr<node> cursor) : _cursor(cursor) {}
            reference_type operator*();
            pointer_type operator->();
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
        _front(nullptr),
        _back(nullptr),
        _count(0) {
            for (auto const& value : list) {
                this->push_back(value);
            }
        }
        doubly_linked_list(size_t count, t const& value) :
        _front(nullptr),
        _back(nullptr),
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
        t front() const { return this->_front ? this->_front->_value : t(); }
        t back() const { return this->_back ? this->_back->_value : t(); }
        iterator_type begin() const { return iterator<t>(this->_front); }
        const_iterator_type cbegin() const { return iterator<t const>(this->_front); }
        iterator_type end() const { return iterator<t>(nullptr); }
        const_iterator_type cend() const { return iterator<t const>(nullptr); }
        reverse_iterator_type rbegin() const { return iterator<t>(this->_back); }
        const_reverse_iterator_type crbegin() const { return iterator<t const>(this->_back); }
        reverse_iterator_type rend() const { return iterator<t>(nullptr); }
        const_reverse_iterator_type crend() const { return iterator<t const>(nullptr); }
    };
}