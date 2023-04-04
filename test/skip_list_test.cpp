//
// Created by 임정운 on 2023/03/29.
//

#include <gtest/gtest.h>
#include <skip_list.h>

TEST(test_suite_skip_list, contain_test) {
    tk::skip_list<int> list(5);

    list.insert(11);
    list.insert(12);
    list.insert(13);

    EXPECT_TRUE(list.is_contain(11));
    EXPECT_TRUE(list.is_contain(12));
    EXPECT_TRUE(list.is_contain(13));
    EXPECT_FALSE(list.is_contain(14));
}

TEST(test_suite_skip_list, insert_test) {
    tk::skip_list<int> list(5, 0.5);

    list.insert(3);
    list.insert(6);
    list.insert(7);
    list.insert(9);
    list.insert(12);

    EXPECT_EQ(list.count(), 5);
    EXPECT_TRUE(list.is_contain(7));
}

TEST(test_suite_skip_list, remove_test) {
    tk::skip_list<int> list(5, 0.5);

    list.insert(3);
    list.insert(6);
    list.insert(7);
    list.insert(9);
    list.insert(12);

    EXPECT_EQ(list.count(), 5);

    list.remove(6);
    list.remove(9);

    EXPECT_EQ(list.count(), 3);
    EXPECT_TRUE(list.is_contain(7));
    EXPECT_TRUE(list.is_contain(12));
    EXPECT_FALSE(list.is_contain(6));
    EXPECT_FALSE(list.is_contain(9));
}