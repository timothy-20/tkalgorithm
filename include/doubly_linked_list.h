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

            explicit node(const t& value) :
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
        class iterator {
        private:
            node* _cursor;

        public:
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::bidirectional_iterator_tag;

            explicit iterator(node* cursor) : _cursor(cursor) {}
            t& operator*() {
                if (this->_cursor == nullptr) {
                    throw std::out_of_range("Unable to access pointer. out of range of array.");
                }

                return this->_cursor->_value;
            }
            node* operator->() { return this->_cursor; }
            iterator& operator+(size_t index) {
                auto temp_cursor(this->_cursor);
                size_t count(0);

                while (temp_cursor) {
                    if (count == index) {
                        break;
                    }

                    temp_cursor = temp_cursor->_next.get();
                    count++;
                }

                return iterator(temp_cursor);
            }
            iterator& operator++() {
                if (this->_cursor) {
                    this->_cursor = this->_cursor->_next;
                }

                return *this;
            }
            iterator operator++(t) {
                iterator temp_iterator(*this);

                if (this->_cursor) {
                    this->_cursor = this->_cursor->_next;
                }

                return temp_iterator;
            }
            iterator& operator-(size_t size) {
                auto temp_cursor(this->_cursor);
                size_t count(0);

                while (temp_cursor) {
                    if (count == size) {
                        break;
                    }

                    temp_cursor = temp_cursor->_prev.get();
                    count++;
                }

                return iterator(temp_cursor);
            }
            iterator& operator--() {
                if (this->_cursor) {
                    this->_cursor = this->_cursor->_prev;
                }

                return *this;
            }
            iterator operator--(t) {
                auto temp_iterator(*this);

                if (this->_cursor) {
                    this->_cursor = this->_cursor->_prev;
                }

                return temp_iterator;
            }
            bool operator==(const iterator& other) const { return this->_cursor == other._cursor; }
            bool operator!=(const iterator& other) const { return this->_cursor != other._cursor; }
        };

    public:
        doubly_linked_list(size_t count, t value) :
        _front(nullptr),
        _back(nullptr),
        _count(count) {
            // ...
            // 멤버 함수를 이용할 의향이 있음
        }
        doubly_linked_list(size_t count) : doubly_linked_list(count, 0) {

        }
        doubly_linked_list() : doubly_linked_list(0) {}
        ~doubly_linked_list() = default;

        void push_front(const t& value) {
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
        void push_back(const t& value) {
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
        void insert(iterator iterator, const t& value) {
//            if (iterator == )
        }
        void remove(iterator iterator) {

        }
        size_t count() const { return this->_count; }
        t front() const { return this->_front ? this->_front->_value : t(); }
        t back() const { return this->_back ? this->_back->_value : t(); }
        iterator begin() { return iterator(this->_front.get()); }
        iterator end() { return iterator(nullptr); }
    };
}