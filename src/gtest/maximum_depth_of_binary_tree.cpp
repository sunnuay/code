#include "tree_node.hpp"
#include <gtest/gtest.h>
#include <vector>

using namespace std;

int max_depth(TreeNode *root) {
  int depth = 0;
  if (root == nullptr) {
    return depth;
  }
  vector<TreeNode *> curr;
  curr.push_back(root);
  while (!curr.empty()) {
    vector<TreeNode *> next;
    for (auto node : curr) {
      if (node->left) {
        next.push_back(node->left);
      }
      if (node->right) {
        next.push_back(node->right);
      }
    }
    curr = next;
    depth++;
  }
  return depth;
}

TEST(maximum_depth_of_binary_tree, basic) {
  TreeNode n5(7), n4(15), n3(20, &n4, &n5), n2(9), n1(3, &n2, &n3);
  EXPECT_EQ(max_depth(&n1), 3);
}
