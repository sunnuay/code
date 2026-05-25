#include "tree_node.hpp"
#include <gtest/gtest.h>
#include <queue>

using namespace std;

bool is_symmetric(TreeNode *root) {
  if (root == nullptr) {
    return true;
  }
  queue<TreeNode *> nodes;
  nodes.push(root->left);
  nodes.push(root->right);
  while (!nodes.empty()) {
    TreeNode *l = nodes.front();
    nodes.pop();
    TreeNode *r = nodes.front();
    nodes.pop();
    if (!l && !r) {
      continue;
    }
    if (!l || !r || l->val != r->val) {
      return false;
    }
    nodes.push(l->left);
    nodes.push(r->right);
    nodes.push(l->right);
    nodes.push(r->left);
  }
  return true;
}

TEST(symmetric_tree, basic) {
  TreeNode n7(3), n6(4), n5(4), n4(3);
  TreeNode n3(2, &n6, &n7), n2(2, &n4, &n5);
  TreeNode n1(1, &n2, &n3);
  EXPECT_TRUE(is_symmetric(&n1));
}
