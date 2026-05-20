#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

using namespace std;

void move_zeroes(vector<int> &nums) {
  int n = nums.size();
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (nums[i] != 0) {
      nums[count] = nums[i];
      count++;
    }
  }
  fill(nums.begin() + count, nums.end(), 0);
}

TEST(move_zeros, basic) {
  vector<int> nums = {0, 1, 0, 3, 12};
  vector<int> want = {1, 3, 12, 0, 0};
  move_zeroes(nums);
  EXPECT_EQ(nums, want);
}
