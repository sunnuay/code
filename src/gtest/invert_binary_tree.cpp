#include "tree_node.hpp"
#include <gtest/gtest.h>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

TreeNode *invert_tree(TreeNode *root) {
  if (root == nullptr) {
    return root;
  }
  queue<TreeNode *> nodes;
  nodes.push(root);
  while (!nodes.empty()) {
    TreeNode *node = nodes.front();
    nodes.pop();
    if (node->left) {
      nodes.push(node->left);
    }
    if (node->right) {
      nodes.push(node->right);
    }
    swap(node->left, node->right);
  }
  return root;
}

TEST(invert_binary_tree, basic) {
  TreeNode n7(9), n6(6), n5(3), n4(1);
  TreeNode n3(7, &n6, &n7), n2(2, &n4, &n5), n1(4, &n2, &n3);
  vector<int> inorder_traversal(TreeNode * node);
  vector<int> vals = inorder_traversal(invert_tree(&n1));
  vector<int> want = {9, 7, 6, 4, 3, 2, 1};
  EXPECT_EQ(vals, want);
}
