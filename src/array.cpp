//
// Created by aircuve on 2023-03-23.
//

#include <array.h>

namespace tk {
    // dynamic array implementation
    template <typename t>
    t* dynamic_array<t>::reallocate(t *list, size_t capacity) {
        auto new_list(new t[capacity]);

        for (int i(0); (i < capacity && &list[i] != nullptr); i++) {
            new_list[i] = list[i];
        }

        return new_list;
    }

    template <typename t>
    void dynamic_array<t>::grow_capacity() {
        this->_capacity *= 2;
        this->_list = dynamic_array<t>::reallocate(this->_list,this->_capacity);
    }

    template <typename t>
    void dynamic_array<t>::shrink_capacity() {
        this->_capacity /= 2;
        this->_list = dynamic_array<t>::reallocate(this->_list,this->_capacity);
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
    void dynamic_array<t>::insert(t value, size_t index) {
        if (this->_count == this->_capacity) {
            this->grow_capacity();
        }

        for (size_t i(this->_count); i > index; i--) {
            this->_list[i] = std::move(this->_list[i - 1]);
        }

        this->_list[index] = value;
        this->_count++;
    }

    template <typename t>
    void dynamic_array<t>::remove_last() {
        this->_list[this->_count] = t();
        this->_count--;

        if (this->_count <= (this->_capacity / 4)) {
            this->shrink_capacity();
        }
    }

    template <typename t>
    void dynamic_array<t>::remove(size_t index) {
        for (size_t i(index); i < this->_count; i++) {
            this->_list[i] = std::move(this->_list[i + 1]);
        }

        this->_count--;

        if (this->_count <= (this->_capacity / 4)) {
            this->shrink_capacity();
        }
    }

    template <typename t>
    t& dynamic_array<t>::operator[](size_t index) {
        if (index >= this->_count) {
            throw std::out_of_range("Unable to access element.");
        }

        return this->_list[index];
    }

    // ...

    template class dynamic_array<int>;
}