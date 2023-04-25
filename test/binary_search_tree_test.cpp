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
    int seed_value[7]{ 4, 2, 6, 1, 3, 5, 7 };
    tk::linked_list_based_bst<int> list;

    for (int value : seed_value) {
        EXPECT_NO_THROW(list.insert(value));
    }

    int correct_value[7]{ 4, 2, 1, 3, 6, 5, 7};
    int count(0);

    EXPECT_NO_THROW(list.traversal_preorder(list.root(), [&correct_value, &count](int& value) {
        EXPECT_EQ(correct_value[count++], value);
    }));
}

TEST(test_suite_binary_search_tree, inorder_traversal_test) {
    int seed_value[7]{ 4, 2, 6, 1, 3, 5, 7 };
    tk::linked_list_based_bst<int> list;

    for (int value : seed_value) {
        EXPECT_NO_THROW(list.insert(value));
    }

    int correct_value[7]{ 1, 2, 3, 4, 5, 6, 7 };
    int count(0);

    EXPECT_NO_THROW(list.traversal_inorder(list.root(), [&correct_value, &count](int& value) {
        EXPECT_EQ(correct_value[count++], value);
    }));
}

TEST(test_suite_binary_search_tree, postorder_traversal_test) {
    int seed_value[7]{ 4, 2, 6, 1, 3, 5, 7 };
    tk::linked_list_based_bst<int> list;

    for (int value : seed_value) {
        EXPECT_NO_THROW(list.insert(value));
    }

    int correct_value[7]{ 1, 3, 2, 5, 7, 6, 4 };
    int count(0);

    EXPECT_NO_THROW(list.traversal_postorder(list.root(), [&correct_value, &count](int& value) {
        EXPECT_EQ(correct_value[count++], value);
    }));
}