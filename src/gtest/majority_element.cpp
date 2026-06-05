#include <gtest/gtest.h>
#include <vector>

using namespace std;

int majority_element(vector<int> &nums) {
  int x = 0;
  int votes = 0;
  for (int num : nums) {
    if (votes == 0) {
      x = num;
    }
    votes += num == x ? 1 : -1;
  }
  return x;
}

TEST(majority_element, basic) {
  vector<int> nums = {3, 2, 3};
  EXPECT_EQ(majority_element(nums), 3);
}
