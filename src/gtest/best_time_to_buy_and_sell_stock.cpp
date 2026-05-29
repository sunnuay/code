#include <algorithm>
#include <climits>
#include <gtest/gtest.h>
#include <vector>

using namespace std;

int max_profit(vector<int> &prices) {
  int cost = INT_MAX;
  int profit = 0;
  for (int price : prices) {
    cost = min(cost, price);
    profit = max(profit, price - cost);
  }
  return profit;
}

TEST(max_profit, basic) {
  vector<int> prices = {7, 1, 5, 3, 6, 4};
  EXPECT_EQ(max_profit(prices), 5);
}
