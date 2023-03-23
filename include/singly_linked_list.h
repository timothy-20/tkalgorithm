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
            t _value;
            node<t>* _next;

            explicit node(t value) :
            _value(value),
            _next(nullptr) {}
            node() : node(t()) {}
            ~node() { delete this->_next; }
        };

    private:
        std::unique_ptr<node<t>> _front;
        size_t _count;

    public:
        explicit singly_linked_list(size_t count = 1) :
        _front(std::make_unique<node<t>>()),
        _count(count) {
        }
        void add_front(t value) {
            auto new_node(new node<t>(value));
            new_node->_next = this->_front;
            this->_front = new_node;
            this->_count++;
        }
        void remove_front() {
            auto next_node(this->_front->_next);
            this->_front->_next = nullptr;
            delete this->_front;
            this->_front = next_node;
            this->_count++;
        }
        void insert_after() {

        }
        void remove_after() {

        }
        t front() const { return this->_front->_value; }
    };
}