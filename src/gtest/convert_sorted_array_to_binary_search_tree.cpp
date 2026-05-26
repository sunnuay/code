#include "tree_node.hpp"
#include <gtest/gtest.h>
#include <span>
#include <vector>

using namespace std;

TreeNode *sorted_array_to_bst(span<int> nums) {
  if (nums.empty()) {
    return nullptr;
  }
  int m = nums.size() / 2;
  TreeNode *node = new TreeNode(nums[m]);
  node->left = sorted_array_to_bst(nums.subspan(0, m));
  node->right = sorted_array_to_bst(nums.subspan(m + 1));
  return node;
}

TEST(convert_sorted_array_to_binary_search_tree, basic) {
  vector<int> nums = {-10, -3, 0, 5, 9};
  vector<int> inorder_traversal(TreeNode * node);
  EXPECT_EQ(inorder_traversal(sorted_array_to_bst(nums)), nums);
}
