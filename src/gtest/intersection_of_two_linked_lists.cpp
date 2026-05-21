#include "list_node.hpp"
#include <gtest/gtest.h>

using namespace std;

ListNode *get_intersection_node(ListNode *head_a, ListNode *head_b) {
  ListNode *x = head_a;
  ListNode *y = head_b;
  while (x != y) {
    x = x == nullptr ? head_b : x->next;
    y = y == nullptr ? head_a : y->next;
  }
  return x;
}

TEST(intersection_of_two_linked_lists, basic) {
  ListNode a5(5), a4(4, &a5), a3(8, &a4), a2(1, &a3), a1(4, &a2);
  ListNode b3(1, &a3), b2(6, &b3), b1(5, &b2);
  EXPECT_EQ(get_intersection_node(&a1, &b1), &a3);
}
