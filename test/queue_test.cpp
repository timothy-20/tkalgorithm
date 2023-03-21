//
// Created by aircuve on 2023-03-20.
//

#include <gtest/gtest.h>
#include <queue.h>

TEST(TestSuite001, ArrayBaseQueueTest001) {
    tk::array_based_queue<int> new_queue(20);
    const int loop_count(3);

    for (int i(1); i <= loop_count; i++) {
        new_queue.enqueue(i);
    }

    for (int j(1); j <= loop_count; j++) {
        EXPECT_EQ(new_queue.dequeue(), j);
    }
}

TEST(TestSuite001, ArrayBaseQueueTest002) {
    tk::array_based_queue<int> new_queue(3);

    for (int i(1); i <= 3; i++) {
        new_queue.enqueue(i);
    }

    new_queue.enqueue(100);
    EXPECT_EQ(new_queue.front(), 1);
    EXPECT_EQ(new_queue.back(), 3);
}

TEST(TestSuite002, LinkedListBaseQueueTest001) {
    tk::linked_list_based_queue<int> new_queue;
    const int loop_count(3);

    for (int i(1); i <= loop_count; i++) {
        new_queue.enqueue(i);
    }

    for (int j(1); j <= loop_count; j++) {
        EXPECT_EQ(new_queue.dequeue(), j);
    }
}

TEST(TestSuite002, LinkedListBaseQueueTest002) {
    auto new_queue(new tk::linked_list_based_queue<int>());

    for (int i(1); i <= 5; i++) {
        new_queue->enqueue(i);
    }

    new_queue->dequeue();
    delete new_queue;
    EXPECT_EQ(new_queue, nullptr);
}