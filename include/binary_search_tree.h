//
// Created by 임정운 on 2023/04/04.
//

#pragma once
#include <iostream>
#include <algorithm>
#include <functional>

namespace tk {
    template <typename value_t, typename node_t>
    class binary_search_tree { // 이진 탐색 트리 인터페이스
    public:
        virtual void search(value_t const& value, std::function<void(node_t parent, node_t current, bool is_left)> const& completion) const = 0;
        virtual void traversal_preorder(node_t root, std::function<void(value_t& value)> const& completion) const = 0;
        virtual void traversal_inorder(node_t root, std::function<void(value_t& value)> const& completion) const = 0;
        virtual void traversal_postorder(node_t root, std::function<void(value_t& value)> const& completion) const = 0;
        virtual void insert(value_t const& value) = 0;
        virtual void remove(value_t const& value) = 0;
    };

    template <typename t>
    class array_based_bst : public binary_search_tree<t, size_t> {
    private:
        size_t _size;
        t* _tree;

    private:
        size_t get_parent_index(size_t index) const {
            return (index - (index % 2 == 1 ? 1 : 2)) / 2;
        }
        size_t get_child_index(size_t index, bool is_left) const {
            return 2 * index + (is_left ? 1 : 2);
        }
        void resize(size_t new_size) {
            if (this->_tree == nullptr) {
                return;
            }

            auto new_tree(new t[new_size]);
            auto end(std::copy(this->_tree, this->_tree + (new_size >= this->_size ? this->_size : new_size), new_tree));
            std::fill(end, new_tree + new_size, t());

            delete[] this->_tree;

            this->_tree = new_tree;
            this->_size = new_size;
        }

    public:
        explicit array_based_bst(size_t size = 14) : // level 3 까지는 기본적으로 할당
        _size(size),
        _tree(new t[size]) {
            std::fill(this->_tree, this->_tree + this->_size, t());
        }
        ~array_based_bst() {
            delete[] this->_tree;
        }
        void search(t const& value, std::function<void(size_t parent, size_t current, bool is_left)> const& completion) const override {
            if (this->_tree[0] == t()) {
                return;
            }

            size_t parent_index(0);
            size_t current_index(0);
            bool is_left(false);

            while (current_index < this->_size) { // 트리의 크기를 넘지 않을 때까지 순회
                if (this->_tree[current_index] == value) {
                    break;
                }

                parent_index = current_index;
                is_left = this->_tree[parent_index] > value;
                current_index = this->get_child_index(parent_index, is_left);
            }

            completion(parent_index, current_index, is_left);
        }
        void traversal_preorder(size_t root, std::function<void(t& value)> const& completion) const override {
            auto index_stack(new size_t[this->_size]);
            long index_stack_cursor(0);
            index_stack[index_stack_cursor] = 0;

            while (index_stack_cursor >= 0) {
                auto current_index(index_stack[index_stack_cursor--]);

                if (current_index >= this->_size || this->_tree[current_index] == t()) {
                    continue;
                }

                completion(this->_tree[current_index]);

                auto right_child_index(this->get_child_index(current_index, false));
                auto left_child_index(this->get_child_index(current_index, true));

                if (right_child_index < this->_size) {
                    index_stack[++index_stack_cursor] = right_child_index;
                }

                if (left_child_index < this->_size) {
                    index_stack[++index_stack_cursor] = left_child_index;
                }
            }

            delete[] index_stack;
        }
        void traversal_inorder(size_t root, std::function<void(t& value)> const& completion) const override {
            auto index_stack(new size_t[this->_size]);
            long index_stack_cursor(-1);
            size_t current_index(0);

            while (index_stack_cursor >= 0 || current_index < this->_size) {
                if (current_index < this->_size && this->_tree[current_index] != t()) { // 현재 인덱스가 가르키고 있는 대상 유효할 경우(우선적으로 왼쪽 노드로 이동하기 위한 조건)
                    index_stack[++index_stack_cursor] = current_index;
                    current_index = this->get_child_index(current_index, true); // 왼쪽 자식의 인덱스 이동

                } else {
                    current_index = index_stack[index_stack_cursor--]; // 적재된 왼쪽 노드의 인덱스 정보를 꺼냄

                    completion(this->_tree[current_index]);

                    current_index = this->get_child_index(current_index, false); // 오른쪽 자식 인덱스 이동
                }
            }

            delete[] index_stack;
        }
        void traversal_postorder(size_t root, std::function<void(t& value)> const& completion) const override {
            auto visited_stack(new bool[this->_size]); // 방문 사실을 기록하는 스택
            auto index_stack(new size_t[this->_size]);
            long stack_cursor(0);
            visited_stack[stack_cursor] = false;
            index_stack[stack_cursor] = 0;

            while (stack_cursor >= 0) {
                auto visited(visited_stack[stack_cursor]);
                auto index(index_stack[stack_cursor]);
                --stack_cursor;

                if (index >= this->_size || this->_tree[index] == t()) { // 인덱스가 최대 범위를 벗어났거나, 값이 유효하지 않은 경우
                    continue;
                }

                if (visited) {
                    completion(this->_tree[index]);

                } else {

                }
            }

            delete[] visited_stack;
            delete[] index_stack;
        }
        void insert(t const& value) override {
            if (this->_tree[0] == t()) { // 루트 인덱스의 값이 초기값인 경우
                this->_tree[0] = value;

                return;
            }

            size_t index(0);

            while (true) {
                if (this->_tree[index] == value) { // 중복된 값이 존재하는 경우 삽입을 중단
                    break;
                }

                auto child_index(this->get_child_index(index, this->_tree[index] > value));

                if (child_index >= this->_size) { // 자식 인덱스가 트리의 크기를 초과할 경우
                    this->resize(child_index*2); // level 1 만큼 확장
                }

                if (this->_tree[child_index] == t()) {
                    this->_tree[child_index] = value;
                    break;
                }

                index = child_index;
            }
        }
        void remove(t const& value) override {

        }
    };

    template <typename t>
    struct node;

    template <typename t>
    class linked_list_based_bst : binary_search_tree<t, node<t>*> {
    private:
        struct node {
            t _value;
            node* _left;
            node* _right;

            explicit node(t const& value) :
                    _value(value),
                    _left(nullptr),
                    _right(nullptr) {}
            node() : node(t()) {}
        };

//    private:
//        size_t _size;
//        node* _root;
//
//    private:
//        void search(t const& value, std::function<void(node* parent, node* current, bool is_left)> completion);
//        void traversal_preorder(node* root, std::function<void(node* target)> completion);
//        void traversal_inorder(node* root, std::function<void(node* target)> completion);
//        void traversal_postorder(node* root, std::function<void(node* target)> completion);
//
//    public:
//        linked_list_based_bst();
//        linked_list_based_bst(std::initializer_list<t> list);
//        explicit linked_list_based_bst(size_t size, t const& value);
//        explicit linked_list_based_bst(size_t size);
//        ~linked_list_based_bst();
//        void insert(t const& value);
//        void remove(t const& value);
    };

    template class binary_search_tree<int, size_t>;
    template class binary_search_tree<int, node<int>*>;
    template class array_based_bst<int>;
    template class linked_list_based_bst<int>;
}