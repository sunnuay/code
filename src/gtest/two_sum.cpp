#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> two_sum(vector<int> &nums, int target) {
  unordered_map<int, int> mp;
  int n = nums.size();
  for (int i = 0; i < n; i++) {
    auto it = mp.find(target - nums[i]);
    if (it != mp.end()) {
      return {it->second, i};
    }
    mp[nums[i]] = i;
  }
  return {};
}

TEST(two_sum, basic) {
  vector<int> nums = {2, 7, 11, 15};
  vector<int> want = {0, 1};
  EXPECT_EQ(two_sum(nums, 9), want);
}
