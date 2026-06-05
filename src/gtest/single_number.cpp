#include <gtest/gtest.h>
#include <vector>

using namespace std;

int single_number(vector<int> &nums) {
  int res = 0;
  for (int num : nums) {
    res ^= num;
  }
  return res;
}

TEST(single_number, basic) {
  vector<int> nums = {2, 2, 1};
  EXPECT_EQ(single_number(nums), 1);
}
