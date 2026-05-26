#include "tree_node.hpp"
#include <algorithm>
#include <gtest/gtest.h>

using namespace std;

int diameter_of_binary_tree(TreeNode *root) {
  int diameter = 0;
  auto dfs = [&](this auto &self, TreeNode *node) -> int {
    if (!node)
      return 0;
    int l = self(node->left);
    int r = self(node->right);
    diameter = max(diameter, l + r);
    return max(l, r) + 1;
  };
  dfs(root);
  return diameter;
}

TEST(diameter_of_binary_tree, basic) {
  TreeNode n5(5), n4(4), n3(3), n2(2, &n4, &n5), n1(1, &n2, &n3);
  EXPECT_EQ(diameter_of_binary_tree(&n1), 3);
}
