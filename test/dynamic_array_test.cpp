//
// Created by aircuve on 2023-03-23.
//

#include <gtest/gtest.h>
#include <dynamic_array.h>

TEST(test_suite_dynamic_array, initialize_test) {
    tk::dynamic_array<int> list1(5, 10);
    tk::dynamic_array<int> list2(3);
    tk::dynamic_array<int> list3;
    tk::dynamic_array<int> list4{ 0, 1, 2, 3};

    for (auto const& value : list1) {
        EXPECT_EQ(value, 10);
    }

    for (auto const& value : list2) {
        EXPECT_EQ(value, 0);
    }

    int count(0);

    for (auto const& value : list3) {
        EXPECT_EQ(value, count);
        count++;
    }

    EXPECT_EQ(list1.count(), 5);
    EXPECT_EQ(list2.count(), 3);
    EXPECT_EQ(list3.count(), 0);
    EXPECT_EQ(list4.count(), 4);
}

TEST(test_suite_dynamic_array, push_back_test) {
    tk::dynamic_array<int> arr(5);

    for (int i(0); i < 5; i++) {
        arr.push_back(i);
    }

    EXPECT_EQ(arr.count(), 10);
    EXPECT_EQ(arr[2], 0);
    EXPECT_EQ(arr[6], 1);
}

TEST(test_suite_dynamic_array, pop_back_test) {
    tk::dynamic_array<int> list{ 1, 2, 3, 4 };

    for (int i(0); i < 2; i++) {
        list.pop_back();
    }

    EXPECT_EQ(list.count(), 2);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 2);
}

TEST(test_suite_dynamic_array, insert_test) {

}

TEST(test_suite_dynamic_array, remove_test) {

}

TEST(test_suite_dynamic_array, resize_test) {

}

TEST(test_suite_dynamic_array, expand_test) {
    tk::dynamic_array<int> list{ 0, 1, 2 };

    EXPECT_EQ(list.capacity(), 6);

    for (int i(0); i < 4; ++i) {
        list.push_back(i);
    }

    EXPECT_EQ(list.capacity(), 12);
    EXPECT_EQ(list[5], 2);
}

TEST(test_suite_dynamic_array, shrink_test) {
    tk::dynamic_array<int> list;

    for (int i(0); i < 12; i++) {
        list.push_back(i);
    }

    EXPECT_EQ(list.capacity(), 20);

    for (int i(0); i < 6; i++) {
        list.pop_back();
    }

    EXPECT_EQ(list.capacity(), 20);

    for (int i(0); i < 3; i++) {
        list.pop_back();
    }

    EXPECT_EQ(list.count(), 3);
    EXPECT_EQ(list.capacity(), 10);
}

TEST(test_suite_dynamic_array, iterator_test) {
    tk::dynamic_array<int> list{ 0, 1, 2, 3, 4 };
    int count1(0);
    int count2(4);

    for (auto const& value : list) {
        EXPECT_EQ(count1, value);

        count1++;
    }

    for (auto i(list.crbegin()); i != list.crend(); i++) {
        EXPECT_EQ(count2, *i);

        count2--;
    }

    EXPECT_EQ(*(list.begin() + 1), 1);
    EXPECT_EQ(*(list.rbegin() + 1), 3);
    EXPECT_EQ(*(list.end() - 1), 4);
    EXPECT_EQ(*(list.rend() - 1), 0);
}