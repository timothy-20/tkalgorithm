//
// Created by jungu on 3/21/2023.
//

#include <iostream>

namespace tk {
    template <typename t>
    class dynamic_array {
    private:
        t* _list;
        uint32_t _capacity;
        uint32_t _count;

    private:
        void expand_capacity() {
            // ...
        }

    public:
        explicit dynamic_array(uint32_t capacity) :
        _list(new t[capacity]),
        _capacity(capacity),
        _count(0) {
        }
        ~dynamic_array() {
            delete[] this->_list;
        }
        void add(t value) {
            if (this->_count == this->_capacity) {
                this->_capacity *= 2;
                auto new_list(new t[this->_capacity]);

                for (int i(0); i < sizeof(this->_list); i++) {
                    new_list[i] = this->_list[i];
                }

                this->_list = new_list;
            }

            this->_list[this->_count] = value;
            this->_count++;
        }
        void insert(t value, uint32_t index) {
            uint32_t start_index(index + 1);
            uint32_t end_index(sizeof(this->_list) - 1);
            size_t bound(end_index - start_index);
            t rest_list[bound];

            for (uint32_t i(start_index); i < end_index; i++) {
                rest_list = this->_list[i];
            }


        }
        void remove(t value, uint32_t index) {

        }
    };
}