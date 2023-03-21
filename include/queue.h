//
// Created by aircuve on 2023-03-20.
//
#pragma once
#include <iostream>

namespace tk {
    template <typename t>
    class queue {
    private:
        template <typename nt>
        struct node {
            t _value;
            node<nt>* _prev;
            node<nt>* _next;

            explicit node(nt value) :
                    _value(value),
                    _prev(nullptr),
                    _next(nullptr) {
            }
            ~node() = default;
        };

    private:
        uint32_t _count;
        node<t>* _front;
        node<t>* _back;

    public:
        explicit queue() :
                _count(0),
                _front(nullptr),
                _back(nullptr) {
        }
        ~queue();
        void enqueue(t value);
        t dequeue() ;
        uint32_t count() const { return this->_count; }
        t front() const { return this->_front ? this->_front->_value : t(); }
        t back() const { return this->_back ? this->_back->_value : t(); }
        bool is_empty() const { return this->_count == 0; }
    };
}
