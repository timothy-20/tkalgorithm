//
// Created by aircuve on 2023-03-23.
//

#include <gtest/gtest.h>
#include <dynamic_array.h>

TEST(test_suite_array, dynamic_array_initialize_test) {

}

TEST(test_suite_array, dynamic_array_add_test) {
    tk::dynamic_array<int> arr(5);

    for (int i(0); i < 5; i++) {
        arr.add(i);
    }

    EXPECT_EQ(arr.count(), 5);
    EXPECT_EQ(arr[2], 2);
}

TEST(test_suite_array, dynamic_array_insert_test) {
    tk::dynamic_array<int> arr(10);

    for (int i(0); i < 5; i++) {
        arr.add(i);
    }

    arr.insert(10, 2);
    EXPECT_EQ(arr[2], 10);
    EXPECT_EQ(arr[3], 2);
    EXPECT_EQ(arr[5], 4);
}

TEST(test_suite_array, dynamic_array_remove_last_object_test) {
    tk::dynamic_array<int> arr(5);

    for (int i(0); i < 5; i++) {
        arr.add(i);
    }

    for (int i(0); i < 3; i++) {
        arr.remove_last();
    }

    EXPECT_EQ(arr.count(), 2);
    EXPECT_EQ(arr[1], 1);
}

TEST(test_suite_array, dynamic_array_remove_test) {
    tk::dynamic_array<int> arr(5);

    for (int i(0); i < 5; i++) {
        arr.add(i);
    }

    arr.remove(2);

    EXPECT_EQ(arr.count(), 4);
    EXPECT_EQ(arr[1], 1);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);
    EXPECT_ANY_THROW(arr[4]);
}

TEST(test_suite_array, dynamic_array_expand_test) {
    tk::dynamic_array<int> arr(3);

    for (int i(0); i < 4; ++i) {
        arr.add(i);
    }

    EXPECT_EQ(arr.capacity(), 6);

    for (int i(0); i < 4; ++i) {
        arr.add(i);
    }

    EXPECT_EQ(arr.capacity(), 12);
    EXPECT_EQ(arr[5], 1);
}

TEST(test_suite_array, dynamic_array_shrink_test) {
    tk::dynamic_array<int> arr(12);

    for (int i(0); i < 12; i++) {
        arr.add(i);
    }

    for (int i(0); i < 6; i++) {
        arr.remove_last();
    }

    EXPECT_EQ(arr.capacity(), 12);

    for (int i(0); i < 3; i++) {
        arr.remove_last();
    }

    EXPECT_EQ(arr.count(), 3);
    EXPECT_EQ(arr.capacity(), 6);
}

