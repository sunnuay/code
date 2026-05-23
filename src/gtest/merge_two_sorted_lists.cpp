#include "list_node.hpp"
#include <gtest/gtest.h>
#include <vector>

using namespace std;

ListNode *merge_two_lists(ListNode *x, ListNode *y) {
  ListNode head;
  ListNode *p = &head;
  while (x != nullptr && y != nullptr) {
    if (x->val <= y->val) {
      p->next = x;
      x = x->next;
    } else {
      p->next = y;
      y = y->next;
    }
    p = p->next;
  }
  p->next = x == nullptr ? y : x;
  return head.next;
}

TEST(merge_two_sorted_lists, basic) {
  ListNode a3(4), a2(2, &a3), a1(1, &a2);
  ListNode b3(4), b2(3, &b3), b1(1, &b2);
  vector<int> vals;
  for (ListNode *n = merge_two_lists(&a1, &b1); n; n = n->next) {
    vals.push_back(n->val);
  }
  vector<int> want = {1, 1, 2, 3, 4, 4};
  EXPECT_EQ(vals, want);
}
