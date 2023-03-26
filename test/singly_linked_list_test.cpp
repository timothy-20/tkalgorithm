//
// Created by aircuve on 2023-03-23.
//

#include <gtest/gtest.h>
#include <singly_linked_list.h>

TEST(test_suite_singly_linked_list, initialize_test) {
    tk::singly_linked_list<int> list;

    EXPECT_EQ(list.count(), 0);
    EXPECT_EQ(list.front(), 0);
}

TEST(test_suite_singly_linked_list, add_front_test) {
    tk::singly_linked_list<int> list;

    for (int i(0); i < 3; i++) {
        list.add_front(i);
    }

    EXPECT_EQ(list.count(), 3);
    EXPECT_EQ(list.front(), 2);
}

TEST(test_suite_singly_linked_list, remove_front_test) {
    tk::singly_linked_list<int> list;

    for (int i(0); i < 3; i++) {
        list.add_front(i);
    }

    EXPECT_EQ(list.count(), 3);

    for (int i(2); i >= 0; i--) {
        EXPECT_EQ(list.front(), i);
        list.remove_front();
    }

    EXPECT_EQ(list.count(), 0);
}

TEST(test_suite_singly_linked_list, insert_after_test_001) {
    tk::singly_linked_list<int> list;

    list.add_front(1);
    list.insert_after(list.begin(), 2);

    auto iterator(list.begin());

    for (int i(1); i < 3; i++) {
        EXPECT_EQ(*(iterator++), i);
    }
}

TEST(test_suite_singly_linked_list, insert_after_test_002) {
    tk::singly_linked_list<int> list;

    list.add_front(2); // 1
    list.add_front(4); // 0
    list.insert_after(0, 3); // insert 3 at 1
    EXPECT_EQ(list.count(), 3);

    auto iterator(list.begin());

    for (int i(4); i > 1; i--) {
        EXPECT_EQ(*(iterator++), i);
    }
}

TEST(test_suite_singly_linked_list, remove_after_test_001) {
    tk::singly_linked_list<int> list;

    list.add_front(1);
    list.add_front(2);
    list.remove_after(list.begin());

    EXPECT_EQ(list.front(), 2);
}

TEST(test_suite_singly_linked_list, remove_after_test_002) {
    tk::singly_linked_list<int> list;

    list.add_front(2); // 2
    list.add_front(3); // 1
    list.add_front(4); // 0
    list.remove_after(0); // remove at 1
    EXPECT_EQ(list.count(), 2);
    EXPECT_EQ(list.front(), 4);
    EXPECT_EQ(*(list.begin() + 1), 2);
}

TEST(test_suite_singly_linked_list, iterator_test_001) {
    tk::singly_linked_list<int> list;

    for (int i(1); i <= 5; i++) {
        list.add_front(i);
    }

    EXPECT_EQ(list.count(), 5);
    EXPECT_EQ(*(list.begin() + 3), 2);
    EXPECT_EQ(*(list.begin() + 1), 4);
    EXPECT_ANY_THROW(*(list.begin() + 10));
}

TEST(test_suite_singly_linked_list, iterator_test_002) {
    tk::singly_linked_list<int> list;

    list.add_front(4);
    list.add_front(3);
    list.add_front(7);

    for (auto& element : list) {
        if (element == 3) {
            element = 6;
        }
    }

    EXPECT_EQ(*(list.begin() + 1), 6);
}

TEST(test_suite_singly_linked_list, iterator_test_003) {
    tk::singly_linked_list<int> list;

    list.add_front(2);
    list.add_front(8);
    list.add_front(6);

    auto iterator(list.begin());

    EXPECT_EQ(*(++iterator), 8);
    EXPECT_EQ(*(iterator++), 8);
    EXPECT_EQ(*iterator, 2);
    EXPECT_TRUE(++iterator == list.end());
}

