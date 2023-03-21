//
// Created by aircuve on 2023-03-20.
//

#include <queue.h>

namespace tk {
    template<typename t>
    queue<t>::~queue() {
        while (this->_count != 0) {
            this->dequeue();
        }
    }

    template<typename t>
    void queue<t>::enqueue(t value) {
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
    t queue<t>::dequeue() {
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

    template class queue<int32_t>;
    template class queue<uint32_t>;
};