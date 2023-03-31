//
// Created by 임정운 on 2023/03/29.
//

#pragma once
#include <iostream>

namespace tk {
    template <typename t>
    class skip_list {
    private:
        struct node {
            t _value;
            node** _forward;

            explicit node(t value, size_t level) :
            _value(value),
            _forward(new node*[level+1]) {
                memset(this->_forward, t(), sizeof(node*) * (level+1));
            }
            ~node() {
                delete[] this->_forward;
            }
        };

    private:
        static int constexpr MAX_LEVEL = 10;
        size_t _level;
        node* _head;

    public:
        skip_list() :
        _level(1),
        _head(new node(t(), MAX_LEVEL)) {
            srand((unsigned int)time(nullptr));
        }
        ~skip_list() {
            delete this->_head;
        }

        void insert_node(t const& value) {
            node* temp(this->_head);
            node* update_node[MAX_LEVEL+1];

            memset(update_node, t(), sizeof(node*) * (MAX_LEVEL+1));

            for (int i(this->_level); i > 0; i--) {
                while (temp->_forward[i] && temp->_forward[i]->_value < value) {

                }

                update_node[i] = temp;
            }
        }
    };
}