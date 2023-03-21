//
// Created by aircuve on 2023-03-20.
//
#pragma once
#include <iostream>

#define QUEUE_MAX_SIZE 101

namespace tk {
    template <typename t>
    class queue {
    public:
        virtual void enqueue(t value) = 0;
        virtual t dequeue() = 0;
        virtual t front() const = 0;
        virtual t back() const = 0;
        virtual uint32_t count() const = 0;
        virtual bool is_empty() const = 0;
    };

    template <typename t>
    class array_based_queue : public queue<t> {
    private:
        t* _values;
        int32_t _front_index;
        int32_t _back_index;
        uint32_t _capacity;
        uint32_t _count;

    public:
        explicit array_based_queue(uint32_t capacity = QUEUE_MAX_SIZE) :
        _values(new t[capacity]),
        _front_index(0),
        _back_index(-1),
        _capacity(capacity),
        _count(0) {}
        virtual ~array_based_queue() { delete[] this->_values; }
        void enqueue(t value);
        t dequeue();
        t front() const { return this->_values[this->_front_index]; }
        t back() const { return this->_values[this->_back_index]; }
        uint32_t count() const { return this->_count; }
        bool is_empty() const { return (this->_count == 0); }
        bool is_full() const { return (this->_count == this->_capacity); }
    };

    template <typename t>
    class linked_list_based_queue : public queue<t> {
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
        explicit linked_list_based_queue() :
        _count(0),
        _front(nullptr),
        _back(nullptr) {}
        virtual ~linked_list_based_queue();
        void enqueue(t value);
        void enqueue_emplace(t& value);
        t dequeue();
        t front() const { return this->_front ? this->_front->_value : t(); }
        t back() const { return this->_back ? this->_back->_value : t(); }
        uint32_t count() const { return this->_count; }
        bool is_empty() const { return this->_count == 0; }
    };
}
