#include <gtest/gtest.h>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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
  EXPECT_EQ(reverse_list(&n1), &n5);
  EXPECT_EQ(n5.next, &n4);
  EXPECT_EQ(n4.next, &n3);
  EXPECT_EQ(n3.next, &n2);
  EXPECT_EQ(n2.next, &n1);
  EXPECT_EQ(n1.next, nullptr);
}
