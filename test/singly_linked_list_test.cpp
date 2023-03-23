//
// Created by aircuve on 2023-03-23.
//

#include <gtest/gtest.h>
#include <singly_linked_list.h>

TEST(test_suite_singly_linked_list, initialize_test) {
    tk::singly_linked_list<int> list;

    EXPECT_EQ(list.front(), 0);
}