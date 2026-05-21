#include "list_node.hpp"
#include <gtest/gtest.h>
#include <vector>

using namespace std;

bool is_palindrome(ListNode *head) {
  vector<int> vals;
  for (auto it = head; it; it = it->next) {
    vals.push_back(it->val);
  }
  int n = vals.size();
  for (int i = 0, j = n - 1; i < j; i++, j--) {
    if (vals[i] != vals[j]) {
      return false;
    }
  }
  return true;
}

TEST(palindrome_linked_list, basic) {
  ListNode n4(1), n3(2, &n4), n2(2, &n3), n1(1, &n2);
  EXPECT_TRUE(is_palindrome(&n1));
}
