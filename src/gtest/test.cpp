#include "../sorting/bubble_sort.c"
#include "../sorting/swap.c"
#include <gtest/gtest.h>

TEST(BubbleSortTest, HandlesUnsortedArray) {
  int arr[] = {5, 1, 4, 2, 8};
  int size = sizeof(arr) / sizeof(arr[0]);
  bubble_sort(arr, size);
  int expected[] = {1, 2, 4, 5, 8};
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(arr[i], expected[i]);
  }
}

TEST(BubbleSortTest, HandlesAlreadySortedArray) {
  int arr[] = {1, 2, 3, 4, 5};
  int size = sizeof(arr) / sizeof(arr[0]);
  int expected[] = {1, 2, 3, 4, 5};
  bubble_sort(arr, size);
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(arr[i], expected[i]);
  }
}

TEST(BubbleSortTest, HandlesArrayWithDuplicates) {
  int arr[] = {5, 8, 5, 2, 2};
  int size = sizeof(arr) / sizeof(arr[0]);
  int expected[] = {2, 2, 5, 5, 8};
  bubble_sort(arr, size);
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(arr[i], expected[i]);
  }
}

TEST(BubbleSortTest, HandlesEmptyAndSingleElementArrays) {
  int empty_arr[] = {};
  bubble_sort(empty_arr, 0);
  int single_arr[] = {42};
  bubble_sort(single_arr, 1);
  EXPECT_EQ(single_arr[0], 42);
}
