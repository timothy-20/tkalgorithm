//
// Created by 임정운 on 2023/03/29.
//

#pragma once
#include <iostream>
#include <cstring>
#include <random>

namespace tk {
    template <typename t>
    class skip_list {
    private:
        struct node {
            t _value;
            node** _forward;

            explicit node(t const& value, size_t level) :
            _value(value),
            _forward(new node*[level+1]) {
                if (std::memset(this->_forward, 0, sizeof(node*) * (level+1)) == nullptr) {
                    throw std::bad_alloc(); // forward 초기화 실패 시, 예외 전이
                }
            }
            ~node() {
                delete[] this->_forward;
            }
        };

    private:
        static int constexpr MAX_LEVEL = 10; // 한 노드가 가질 수 있는 최대 레벨
        size_t _count;
        node* _head;

    public:
        skip_list() try :
        _count(1), // head가 존재하므로 1로 초기화
        _head(new node(t(), MAX_LEVEL)) {

        } catch (std::exception e) { // function try
            delete this->_head;
            throw e;
        }
        ~skip_list() {
            delete this->_head;
        }

        uint32_t get_random_level() const {
            std::random_device rd;
            std::mt19937 generator(rd());
            std::uniform_int_distribution<> distribution(0, RAND_MAX);
            uint32_t level(1);

            while (distribution(generator) % 2 == 0 && level < MAX_LEVEL) {
                level++;
            }

            return level;
        }

        void insert(t const& value) {
            node* temp(this->_head);
            node* update_node[MAX_LEVEL+1];

            std::memset(update_node, 0, sizeof(node*) * (MAX_LEVEL+1));

            for (int i(this->_count); i > 0; i--) {
                while (temp->_forward[i] && temp->_forward[i]->_value < value) {
                    temp = temp->_forward[i];
                }

                update_node[i] = temp;
            }

            if (temp->_forward[1] && temp->_forward[1]->_value == value) {
                return;
            }

            int level(this->get_random_level());

            if (level > this->_count) {
                for (int i(this->_count+1); i < level; i++) {
                    update_node[i] = this->_head;
                }

                this->_count = level;
            }
        }
        size_t count() const { return this->_count; }

    };

    template class skip_list<int>;
}