#include <gtest/gtest.h>
#include <vector>

using namespace std;

int search_insert(vector<int> &nums, int target) {
  int l = 0;
  int r = nums.size() - 1;
  while (l <= r) {
    int m = (l + r) / 2;
    if (target == nums[m]) {
      return m;
    }
    if (target < nums[m]) {
      r = m - 1;
    } else {
      l = m + 1;
    }
  }
  return l;
}

TEST(search_insert_position, basic) {
  vector<int> nums = {1, 3, 5, 6};
  EXPECT_EQ(search_insert(nums, 5), 2);
}
