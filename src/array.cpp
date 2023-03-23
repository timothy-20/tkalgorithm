//
// Created by aircuve on 2023-03-23.
//

#include <array.h>

namespace tk {
    template <typename t>
    t* reallocate(t *list, uint32_t capacity) {
        auto new_list(new t[capacity]);

        for (int i(0); (i < capacity && &list[i] != nullptr); i++) {
            new_list[i] = list[i];
        }

        return new_list;
    }

    template <typename t>
    void dynamic_array<t>::grow_capacity() {
        this->_capacity *= 2;
        this->_list = reallocate<t>(this->_list,this->_capacity);
    }

    template <typename t>
    void dynamic_array<t>::shrink_capacity() {
        this->_capacity /= 2;
        this->_list = reallocate<t>(this->_list,this->_capacity);
    }

    template <typename t>
    void dynamic_array<t>::add(t value) {
        if (this->_count == this->_capacity) {
            this->grow_capacity();
        }

        this->_list[this->_count] = value;
        this->_count++;
    }

    template <typename t>
    void dynamic_array<t>::insert(t value, uint32_t index) {
        if (this->_count == this->_capacity) {
            this->grow_capacity();
        }

        uint32_t start_index(index + 1);

        while (&this->_list[start_index] != nullptr) {
            this->_list[start_index++] = std::move(this->_list[start_index - 1]);
        }

        this->_list[index] = value;
        this->_count++;
    }

    template <typename t>
    void dynamic_array<t>::remove_last_object() {
        &this->_list[this->_count] == nullptr;
        this->_count--;

        if (this->_count <= (this->_capacity / 4)) {
            this->shrink_capacity();
        }
    }

    template <typename t>
    void dynamic_array<t>::remove(t value, uint32_t index) {
        &this->_list[index] = nullptr;
        this->_count--;
        uint32_t start_index(index);

        while (&this->_list[start_index] == nullptr) {
            this->_list[start_index] = std::move(this->_list[++start_index]);
        }

        if (this->_count <= (this->_capacity / 4)) {
            this->shrink_capacity();
        }
    }
}