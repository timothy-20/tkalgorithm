//
// Created by 임정운 on 2023/04/04.
//

#include <iostream>
#include <gtest/gtest.h>

#include <array_list_based_bst.h>
#include <linked_list_based_bst.h>

//TEST(test_suite_binary_search_tree, initialize_test) {
//}
//
//TEST(test_suite_binary_search_tree, insert_test) {
//}
//
//TEST(test_suite_binary_search_tree, remove_test) {
//}

// treversal
TEST(test_suite_binary_search_tree, preorder_traversal_test) {
    int seed_value[7] { 1, 2, 3, 4, 5, 6, 7 };
    tk::linked_list_based_bst<int> list;

    for (int value : seed_value) {
        list.insert(value);
    }

    list.traversal_preorder(list.root(), [](int& value) {
        std::cout << value << ' ';
    });
}

TEST(test_suite_binary_search_tree, inorder_traversal_test) {
    int seed_value[7] { 1, 2, 3, 4, 5, 6, 7 };
    tk::linked_list_based_bst<int> list;

    for (int value : seed_value) {
        list.insert(value);
    }

    list.traversal_inorder(list.root(), [](int& value) {
        std::cout << value << ' ';
    });
}

TEST(test_suite_binary_search_tree, postorder_traversal_test) {

}