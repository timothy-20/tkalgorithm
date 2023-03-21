//
// Created by aircuve on 2023-03-20.
//

#include <queue.h>

namespace tk {
    // array_based_queue implementation
    template<typename t>
    void array_based_queue<t>::enqueue(t value) {
        if (this->is_full()) {
            return;
        }

        this->_back_index = (this->_back_index + 1) % this->_capacity;
        this->_values[this->_back_index] = value;
        this->_count++;
    }
    template <typename t>
    t array_based_queue<t>::dequeue() {
        if (this->is_full()) {
            return t();
        }

        t temp_value(this->_values[this->_front_index]);
        this->_front_index = (this->_front_index + 1) % this->_capacity;
        this->_count--;

        return temp_value;
    }

    // linked_list_based_queue implementation
    template<typename t>
    linked_list_based_queue<t>::~linked_list_based_queue() {
        auto temp_node(this->_front);

        while (temp_node != nullptr) {
            auto next_node(temp_node->_next);
            delete temp_node;
            temp_node = next_node;
        }
    }
    template<typename t>
    void linked_list_based_queue<t>::enqueue(t value) {
        auto new_node(new node<t>(value));

        if (this->_front == nullptr) {
            this->_front = new_node;
            this->_back = new_node;
            this->_front->_next = this->_back;
            this->_back->_prev = this->_front;

        } else {
            this->_back->_next = new_node;
            new_node->_prev = this->_back;
            this->_back = new_node;
        }

        this->_count++;
    }
    template <typename t>
    void linked_list_based_queue<t>::enqueue_emplace(t &value) {

    }
    template <typename t>
    t linked_list_based_queue<t>::dequeue() {
        if (this->_front == nullptr) {
            return t();
        }

        auto temp_node(this->_front);
        this->_front = this->_front->_next;

        if (this->_front != nullptr) {
            this->_front->_prev = nullptr;
        }

        this->_count--;
        temp_node->_next = nullptr;
        t value(temp_node->_value);
        delete temp_node;

        return value;
    }

    template class array_based_queue<int>;
    template class linked_list_based_queue<int>;
};