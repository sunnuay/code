#include "list_node.hpp"
#include <gtest/gtest.h>

bool has_cycle(ListNode *head) {
  if (head == nullptr) {
    return false;
  }
  ListNode *slow = head;
  ListNode *fast = head->next;
  while (slow != fast) {
    if (fast == nullptr || fast->next == nullptr) {
      return false;
    }
    slow = slow->next;
    fast = fast->next->next;
  }
  return true;
}

TEST(linked_list_cycle, basic) {
  ListNode n4(-4), n3(0, &n4), n2(2, &n3), n1(3, &n2);
  n4.next = &n2;
  EXPECT_TRUE(has_cycle(&n1));
}
