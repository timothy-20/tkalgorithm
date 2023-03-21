//
// Created by jungu on 3/21/2023.
//

#include <iostream>

namespace tk {
    template <typename t>
    class dynamic_array {
    private:
        t* _values;
        uint32_t _capacity;
        uint32_t _count;
        uint32_t _realloc_count;

    private:
//        void adjust_capacity() {
//        }

    public:
        explicit dynamic_array(uint32_t capacity) :
        _values(new t[capacity]),
        _capacity(capacity),
        _count(0),
        _realloc_count(0) {
        }
        ~dynamic_array() {
            delete[] this->_values;
        }
        void add(t value) {
            if (this->_count > this->_capacity) {
                this->_capacity *= 2;
                auto new_list(new t[this->_capacity]);

                for (int i(0); i < sizeof(this->_values); i++) {
                    new_list[i] = this->_values[i];
                }
            }

            this->_values[this->_count] = value;
            this->_count++;
        }
        void insert(t value, uint32_t index) {

        }
        void remove(t value, uint32_t index) {

        }
    };
}