//
// Created by 임정운 on 2023/04/04.
//

#include <gtest/gtest.h>
#include <binary_search_tree.h>

TEST(test_suite_binary_search_tree, initialize_test) {

}

TEST(test_suite_binary_search_tree, insert_test) {
    tk::binary_search_tree<int> tree;

    tree.insert(10);
    tree.insert(20);
}