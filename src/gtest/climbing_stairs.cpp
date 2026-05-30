#include <gtest/gtest.h>

int climb_stairs(int n) {
  int a = 0;
  int b = 1;
  for (int i = 0; i < n; i++) {
    int t = a + b;
    a = b;
    b = t;
  }
  return b;
}

TEST(climb_stairs, basic) { EXPECT_EQ(climb_stairs(2), 2); }
