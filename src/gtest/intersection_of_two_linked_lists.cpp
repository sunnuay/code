#include <gtest/gtest.h>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

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
  ListNode a1(4), a2(1), a3(8), a4(4), a5(5);
  ListNode b1(5), b2(6), b3(1);
  a1.next = &a2, a2.next = &a3, a3.next = &a4, a4.next = &a5;
  b1.next = &b2, b2.next = &b3, b3.next = &a3;
  EXPECT_EQ(get_intersection_node(&a1, &b1), &a3);
}
