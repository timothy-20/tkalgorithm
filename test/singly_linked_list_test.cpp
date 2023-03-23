//
// Created by aircuve on 2023-03-23.
//

#include <gtest/gtest.h>
#include <singly_linked_list.h>

TEST(test_suite_singly_linked_list, initialize_test) {
    tk::singly_linked_list<int> list;

    EXPECT_EQ(list.front(), 0);
    EXPECT_EQ(list.count(), 1);
}

TEST(test_suite_singly_linked_list, add_front_test) {
    tk::singly_linked_list<int> list;

    for (int i(0); i < 3; i++) {
        list.add_front(i);
    }

    EXPECT_EQ(list.count(), 3);
    EXPECT_EQ(list.front(), 2);
}