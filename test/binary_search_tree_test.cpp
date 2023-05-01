//
// Created by 임정운 on 2023/04/04.
//

#include <gtest/gtest.h>
#include <linked_list_based_bst.h>

//TEST(test_suite_binary_search_tree, initialize_test) {
//}

TEST(test_suite_binary_search_tree, insert_test) {
    tk::linked_list_based_bst<int> tree;

    tree.insert(5);
    tree.insert(7);
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);

    // 이미 트리에 존재하는 값 삽입
    tree.insert(2);
}

TEST(test_suite_binary_search_tree, remove_test) {

}

// treversal
TEST(test_suite_binary_search_tree, preorder_traversal_test) {
    int seed_value[7]{ 4, 2, 6, 1, 3, 5, 7 };
    tk::linked_list_based_bst<int> tree;

    for (int value : seed_value) {
        EXPECT_NO_THROW(tree.insert(value));
    }

    int correct_value[7]{ 4, 2, 1, 3, 6, 5, 7};
    int count(0);

    EXPECT_NO_THROW(tree.traversal_preorder(tree.root(), [&correct_value, &count](int& value) {
        EXPECT_EQ(correct_value[count++], value);
    }));
}

TEST(test_suite_binary_search_tree, inorder_traversal_test) {
    int seed_value[7]{ 4, 2, 6, 1, 3, 5, 7 };
    tk::linked_list_based_bst<int> tree;

    for (int value : seed_value) {
        EXPECT_NO_THROW(tree.insert(value));
    }

    int correct_value[7]{ 1, 2, 3, 4, 5, 6, 7 };
    int count(0);

    EXPECT_NO_THROW(tree.traversal_inorder(tree.root(), [&correct_value, &count](int& value) {
        EXPECT_EQ(correct_value[count++], value);
    }));
}

TEST(test_suite_binary_search_tree, postorder_traversal_test) {
    int seed_value[7]{ 4, 2, 6, 1, 3, 5, 7 };
    tk::linked_list_based_bst<int> tree;

    for (int value : seed_value) {
        EXPECT_NO_THROW(tree.insert(value));
    }

    int correct_value[7]{ 1, 3, 2, 5, 7, 6, 4 };
    int count(0);

    EXPECT_NO_THROW(tree.traversal_postorder(tree.root(), [&correct_value, &count](int& value) {
        EXPECT_EQ(correct_value[count++], value);
    }));
}