#include "list_node.hpp"
#include <gtest/gtest.h>
#include <vector>

using namespace std;

ListNode *reverse_list(ListNode *head) {
  ListNode *prev = nullptr;
  ListNode *curr = head;
  ListNode *temp;
  while (curr) {
    temp = curr->next;
    curr->next = prev;
    prev = curr;
    curr = temp;
  }
  return prev;
}

TEST(reverse_linked_list, basic) {
  ListNode n5(5), n4(4, &n5), n3(3, &n4), n2(2, &n3), n1(1, &n2);
  vector<int> vals;
  for (ListNode *n = reverse_list(&n1); n; n = n->next) {
    vals.push_back(n->val);
  }
  vector<int> want = {5, 4, 3, 2, 1};
  EXPECT_EQ(vals, want);
}
