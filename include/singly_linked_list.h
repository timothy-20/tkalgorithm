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
            t& operator*() {
                if (this->_cursor == nullptr) {
                    throw std::runtime_error("Unable to access, this pointer is nullptr.");
                }

                return this->_cursor->_value;
            }
            iterator operator+(size_t index) {
                size_t count(0);
                node* temp_node(this->_cursor);

                while (temp_node) {
                    if (count == index)
                        break;

                    temp_node = temp_node->_next.get();
                    count++;
                }

                return iterator(temp_node);
            }
            iterator& operator++() {
                if (this->_cursor) {
                    this->_cursor = this->_cursor->_next.get();
                }

                return *this;
            }
            iterator operator++(t) {
                iterator temp(*this);

                if (this->_cursor) {
                    this->_cursor = this->_cursor->_next.get();
                }

                return temp;
            }
            bool operator==(const iterator& other) const { return this->_cursor == other._cursor; }
            bool operator!=(const iterator& other) const { return this->_cursor != other._cursor; }
        };

    public:
        explicit singly_linked_list() :
        _front(nullptr),
        _count(0) {}
        ~singly_linked_list() = default;
        void add_front(const t& value) {
            auto new_node(std::make_unique<node>(value));
            new_node->_next = std::move(this->_front);
            this->_front = std::move(new_node);
            this->_count++;
        }
        void remove_front() {
            if (this->_front) {
                this->_front = this->_front->_next;
                this->_count--;
            }
        }
        void insert_after(uint32_t index) {

        }
        void remove_after(uint32_t index) {

        }
        t front() const {
            if (this->_front == nullptr) {
                throw std::runtime_error("Unable to access, front node pointer is nullptr.");
            }

            return this->_front->_value;
        }
        size_t count() const { return this->_count; }
        iterator begin() const { return iterator(this->_front.get()); }
        iterator end() const { return iterator(nullptr); }
    };
}