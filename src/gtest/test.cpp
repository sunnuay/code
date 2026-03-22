#include <gtest/gtest.h>

int factorial(int n) {
  if (n < 0)
    return 0;
  if (n == 0)
    return 1;
  int result = 1;
  for (int i = 1; i <= n; i++) {
    result *= i;
  }
  return result;
}

TEST(factorial_test, negative_input) {
  EXPECT_EQ(factorial(-2), 0);
  EXPECT_EQ(factorial(-1), 0);
}

TEST(factorial_test, positive_input) {
  EXPECT_EQ(factorial(0), 1);
  EXPECT_EQ(factorial(1), 1);
  EXPECT_EQ(factorial(2), 2);
  EXPECT_EQ(factorial(3), 6);
}
