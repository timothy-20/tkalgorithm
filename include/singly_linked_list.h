//
// Created by aircuve on 2023-03-23.
//

#pragma once
#include <iostream>
#include <memory>

namespace tk {
    template<typename t>
    class singly_linked_list {
    public:
        template <typename it>
        class iterator {
        public:
            using value_type = t;
            using pointer_type = t*;
            using reference_type = t&;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

            explicit iterator(pointer_type value) : _pointer_value(value) {}
            reference_type operator*() { return *this->_pointer_value; }
            pointer_type operator->() { return this->_pointer_value; }
            iterator<it>& operator++() {
                ++this->_pointer_value;

                return *this;
            }
            iterator<it> operator++(it) {
                iterator<it> temp(*this);
                this->_pointer_value++;

                return temp;
            }
            bool operator==(const iterator<it>& other) { return this->_pointer_value == other._pointer_value; }
            bool operator!=(const iterator<it>& other) { return this->_pointer_value != other._pointer_value; }

        private:
            pointer_type _pointer_value;
        };

    public:
        explicit singly_linked_list() :
        _front(nullptr),
        _count(0) {}
        ~singly_linked_list() = default;
        void add_front(const t& value) {
            auto new_node(std::make_unique<node<t>>(value));
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
        t front() const { return this->_front->_value; }
        size_t count() const { return this->_count; }

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
        std::unique_ptr<node<t>> _front;
        size_t _count;
    };
}