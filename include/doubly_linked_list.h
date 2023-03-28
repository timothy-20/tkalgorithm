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
            reference_type operator*() {
                if (this->_cursor == nullptr) {
                    throw std::out_of_range("Unable to access pointer. out of range of array.");
                }

                return this->_cursor->_value;
            }
            pointer_type operator->() { return &this->_cursor->_value; }
            virtual iterator operator+(size_t size) {
                auto temp_cursor(this->_cursor);
                size_t count(0);

                while (temp_cursor) {
                    if (count == size) {
                        break;
                    }

                    temp_cursor = temp_cursor->_next;
                    count++;
                }

                return iterator(temp_cursor);
            }
            virtual iterator& operator++() {
                if (this->_cursor) {
                    this->_cursor = this->_cursor->_next;
                }

                return *this;
            }
            virtual iterator operator++(value_type) {
                auto temp_iterator(*this);

                if (this->_cursor) {
                    this->_cursor = this->_cursor->_next;
                }

                return temp_iterator;
            }
            virtual iterator operator-(size_t size) {
                auto temp_cursor(this->_cursor);
                size_t count(0);

                while (temp_cursor) {
                    if (count == size) {
                        break;
                    }

                    temp_cursor = temp_cursor->_prev;
                    count++;
                }

                return iterator(temp_cursor);
            }
            virtual iterator& operator--() {
                if (this->_cursor) {
                    this->_cursor = this->_cursor->_prev;
                }

                return *this;
            }
            virtual iterator operator--(value_type) {
                auto temp_iterator(*this);

                if (this->_cursor) {
                    this->_cursor = this->_cursor->_prev;
                }

                return temp_iterator;
            }
            bool operator==(iterator const& other) const { return this->_cursor == other._cursor; }
            bool operator!=(iterator const& other) const { return this->_cursor != other._cursor; }
        };

        template <typename rit>
        class reverse_iterator : public iterator<rit> {
        public:
            reverse_iterator(std::shared_ptr<node> cursor) : iterator<rit>(cursor) {}
            reverse_iterator(const iterator<rit>& base) : iterator<rit>(base) {}
            iterator<rit> operator+(size_t size) override {
                return iterator<rit>::operator-(size);
            }
            iterator<rit>& operator++() override {
                *this = iterator<rit>::operator--();

                return *this;
            }
            iterator<rit> operator++(typename iterator<rit>::value_type) override {
                iterator<rit>::operator--(rit());

                return *this;
            }
            iterator<rit> operator-(size_t size) override {
                return iterator<rit>::operator+(size);
            }
            iterator<rit>& operator--() override {
                *this = iterator<rit>::operator++();

                return *this;
            }
            iterator<rit> operator--(typename iterator<rit>::value_type) override {
                iterator<rit>::operator++(rit());

                return *this;
            }
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

        void push_front(t const& value) {
            auto new_node(std::make_shared<node>(value));

            if (this->_front == nullptr) {
                this->_front = new_node;
                this->_back = new_node;

            } else {
                new_node->_next = this->_front;
                this->_front->_prev = new_node;
                this->_front = new_node;
            }

            this->_count++;
        }
        void pop_front() {
            if (this->_front == nullptr) {
                return;
            }

            if (this->_front == this->_back) {
                this->_front = nullptr;
                this->_back = nullptr;

            } else {
                this->_front = this->_front->_next;
                this->_front->_prev = nullptr;
            }

            this->_count--;
        }
        void push_back(t const& value) {
            auto new_node(std::make_shared<node>(value));

            if (this->_front == nullptr) {
                this->_front = new_node;
                this->_back = new_node;

            } else {
                new_node->_prev = this->_back;
                this->_back->_next = new_node;
                this->_back = new_node;
            }

            this->_count++;
        }
        void pop_back() {
            if (this->_back == nullptr) {
                return;
            }

            if (this->_back == this->_front) {
                this->_front = nullptr;
                this->_back = nullptr;

            } else {
                this->_back = this->_back->_prev;
                this->_back->_next = nullptr;
            }

            this->_count--;
        }
        void insert(const_iterator_type iterator, t const& value) {
            if (iterator == this->cend()) {
                throw std::out_of_range("Unable to insert node to doubly linked list. out of range of array.");
            }

            auto prev_node(iterator._cursor->_prev);
            auto new_node(std::make_shared<node>(value));
            new_node->_next = iterator._cursor;
            iterator._cursor->_prev = new_node;
            new_node->_prev = prev_node;
            prev_node->_next = new_node;
            this->_count++;
        }
        void remove(const_iterator_type iterator) {
            if (iterator == this->cend()) {
                throw std::out_of_range("Unable to remove node to doubly linked list. out of range of array.");
            }

            auto prev_node(iterator._cursor->_prev);
            auto next_node(iterator._cursor->_next);
            prev_node->_next = next_node;
            next_node->_prev = prev_node;
            this->_count--;
        }
        size_t count() const { return this->_count; }
        t front() const { return this->_front ? this->_front->_value : t(); }
        t back() const { return this->_back ? this->_back->_value : t(); }
        iterator_type begin() const { return iterator<t>(this->_front); }
        const_iterator_type cbegin() const { return iterator<t const>(this->_front); }
        iterator_type end() const { return iterator<t>(nullptr); }
        const_iterator_type cend() const { return iterator<t const>(nullptr); }
        reverse_iterator_type rbegin() const { return reverse_iterator<t>(this->_back); }
        const_reverse_iterator_type crbegin() const { return reverse_iterator<t const>(this->_back); }
        reverse_iterator_type rend() const { return reverse_iterator<t>(nullptr); }
        const_reverse_iterator_type crend() const { return reverse_iterator<t const>(nullptr); }
    };
}