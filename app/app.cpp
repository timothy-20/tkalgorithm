//
// Created by aircuve on 2023-03-21.
//

#include <cstdlib>
#include <iostream>
#include <stack>
#include <queue>
#include <type_traits>
#include <functional>
#include <queue.h>

template <typename t>
class node {
private:
    enum class _order_type : char {
        none = 'n',
        left = 'l',
        right = 'r'
    };

private:
    t _value;
    node<t>* _parent;
    node<t>* _left;
    node<t>* _right;
    _order_type _order;
    bool _is_leaf;

private:
    void set_order(_order_type order) {
        this->_order = order;
    }

public:
    using order_type = _order_type;

    explicit node(t value) :
            _value(value),
            _parent(nullptr),
            _left(nullptr),
            _right(nullptr),
            _order(_order_type::none),
            _is_leaf(true) {
    }
    ~node() {
        if (this->_left != nullptr)
            delete this->_left;

        if (this->_right != nullptr)
            delete this->_right;
    }
    void set_parent(node<t>* parent) {
        this->_parent = parent;
        this->_is_leaf = false;
    }
    node<t>* remove_from_parent() {
        if (this->_parent == nullptr) {
            return nullptr;
        }

        switch (this->_order) {
            case _order_type::left: this->_parent->remove_left(); break;
            case _order_type::right: this->_parent->remove_right(); break;
            default: return nullptr;
        }

        node<t>* ejected_node(this->_parent);
        this->_parent = nullptr;

        return ejected_node;
    }
    void insert_left(node<t>* left) {
        this->_is_leaf = false;
        left->set_parent(this);
        left->set_order(_order_type::left);

        this->_left = left;
    }
    void insert_right(node<t>* right) {
        this->_is_leaf = false;
        right->set_parent(this);
        right->set_order(_order_type::right);

        this->_right = right;
    }
    node<t>* remove_left() {
        node<t>* ejected_node(this->_left);
        this->_left = nullptr;

        if (this->_right == nullptr) {
            this->_is_leaf = true;
        }

        return ejected_node;
    }
    node<t>* remove_right() {
        node<t>* ejected_node(this->_right);
        this->_right = nullptr;

        if (this->_left == nullptr) {
            this->_is_leaf = true;
        }

        return ejected_node;
    }
    t value() const {
        return this->_value;
    }
    node<t>* parent() const {
        return this->_parent;
    }
    node<t>* left() const {
        return this->_left;
    }
    node<t>* right() const {
        return this->_right;
    }
    _order_type order() const {
        return this->_order;
    }
    bool is_leaf() const {
        return this->_is_leaf;
    }
};

template <typename t>
class binary_tree {
    using node_order = typename node<t>::order_type;

private:
    uint32_t _level;
    node<t>* _root_node;

private:
    static void _binary_search(t target_value, node<t>* root_node, std::function<void(node<t>*, node_order)> callback) {
        node<t>* temp_node(root_node);

        while (temp_node != nullptr) {
            if (target_value > temp_node->value()) {
                if (temp_node->right() == nullptr) {
                    callback(temp_node, node_order::right);

                    temp_node = nullptr;

                } else {
                    temp_node = temp_node->right();
                }

            } else if (target_value < temp_node->value()) {
                if (temp_node->left() == nullptr) {
                    callback(temp_node, node_order::left);

                    temp_node = nullptr;

                } else {
                    temp_node = temp_node->left();
                }

            } else {
                callback(temp_node, node_order::none);

                temp_node = nullptr;
            }
        }
    }
    static void _insert(t target_value, node<t>* root_node) {
        binary_tree::_binary_search(target_value, root_node, [&target_value](node<t>* receive_node, node_order order) {
            if (order == node_order::left) {
                receive_node->insert_left(new node<t>(target_value));

            } else if (order == node_order::right) {
                receive_node->insert_right(new node<t>(target_value));
            }
        });
    }
    static void _remove(t target_value, node<t>* root_node) {
        binary_tree::_binary_search(target_value, root_node, [&root_node](node<t>* receive_node, node_order order) {
            if (order == node_order::none) {
                if (receive_node->is_leaf()) {
                    receive_node->remove_from_parent();

                } else {
                    node<t>* parent_node(receive_node->remove_from_parent());
                    binary_tree::preorder(receive_node, [receive_node, &parent_node](node<t>* next_node) {
                        if (receive_node->value() == next_node->value()) {
                            return;
                        }

                        binary_tree::_insert(next_node->value(), parent_node);
                    });

                    if (root_node->value() > parent_node->value()) {
                        root_node->insert_left(parent_node);

                    } else {
                        root_node->insert_right(parent_node);
                    }
                }
            }
        });
    }
    ///
    /// \param target_node 전위 순위를 할 대상 노드에 대한 인자입니다.
    /// \param callback 순회하는 동안 거치는 노드를 인자로 갖는 람다식입니다.
    ///
    static void preorder(node<t>* target_node, std::function<void(node<t>*)> callback) {
        std::queue<node<t>*> node_queue;

        node_queue.push(target_node);

        while (!node_queue.empty()) {
            auto temp(node_queue.front());

            node_queue.pop();
            callback(temp);

            if (temp->left() != nullptr) {
                node_queue.push(temp->left());
            }

            if (temp->right() != nullptr) {
                node_queue.push(temp->right());
            }
        }
    }
    void left_rotate(node<t>* target_node) {
        if (target_node == nullptr || target_node->right() == nullptr) {
            return;
        }

        node<t>* temp_node(target_node->right());
        target_node->insert_right(target_node->right()->left());

        if (target_node->right() != nullptr) {

        }
    }

public:
    explicit binary_tree() :
            _level(1),
            _root_node(nullptr) {
    }
    explicit binary_tree(t value) : binary_tree() {
        this->_root_node = new node<t>(value);
    }
    ~binary_tree() {
        this->_level = 0;
        delete this->_root_node;
    }
    void insert(t target_value) {
        if (this->_root_node == nullptr) {
            this->_root_node = new node<t>(target_value);

            return;
        }

        binary_tree::_insert(target_value, this->_root_node);
    }
    void remove(t target_value) {
        binary_tree::_remove(target_value, this->_root_node);
    }
    node<t>* root_node() const {
        return this->_root_node;
    }
    static void _print_node_preorder_v1(node<t>* root_node) {
        if (root_node == nullptr)
            return;

        if (root_node->parent() != nullptr)
            std::cout << "node(" << root_node->value() << ") parent value: " << root_node->parent()->value() << '\n';

        std::cout << "node(" << root_node->value() << ") order: " << (char)root_node->order() << '\n';
        binary_tree::_print_node_preorder_v1(root_node->left());
        binary_tree::_print_node_preorder_v1(root_node->right());
    }
    void print_node_prepare_v1() {
        binary_tree::_print_node_preorder_v1(this->_root_node);
    }
    void print_node_prepare_v2() {
        binary_tree::preorder(this->_root_node, [](node<t>* obj) {
            if (obj->parent() != nullptr)
                std::cout << "node(" << obj->value() << ") parent value: " << obj->parent()->value() << '\n';

            std::cout << "node(" << obj->value() << ") order: " << (char)obj->order() << '\n';
        });
    }
};

struct box {
    int* _value;

    explicit box(int value) : _value(new int(value)) {
    }
    ~box() {
        delete this->_value;
    }
};

int main() {

    return 0;
}
