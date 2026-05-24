#include "tree_node.hpp"
#include <gtest/gtest.h>
#include <stack>
#include <vector>

using namespace std;

vector<int> inorder_traversal(TreeNode *node) {
  vector<int> vals;
  stack<TreeNode *> stack;
  while (node || !stack.empty()) {
    if (node) {
      stack.push(node);
      node = node->left;
    } else {
      node = stack.top();
      stack.pop();
      vals.push_back(node->val);
      node = node->right;
    }
  }
  return vals;
}

TEST(binary_tree_inorder_traversal, basic) {
  TreeNode n3(3), n2(2, &n3, nullptr), n1(1, nullptr, &n2);
  vector<int> want = {1, 3, 2};
  EXPECT_EQ(inorder_traversal(&n1), want);
}
