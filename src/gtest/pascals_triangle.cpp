#include <gtest/gtest.h>
#include <vector>

using namespace std;

vector<vector<int>> generate(int rows) {
  vector<vector<int>> res(rows);
  for (int i = 0; i < rows; i++) {
    res[i].resize(i + 1);
    res[i][0] = 1;
    for (int j = 1; j < i; j++) {
      res[i][j] = res[i - 1][j - 1] + res[i - 1][j];
    }
    res[i][i] = 1;
  }
  return res;
}

TEST(pascals_triangle, basic) {
  vector<vector<int>> want = {{1}, //
                              {1, 1},
                              {1, 2, 1},
                              {1, 3, 3, 1},
                              {1, 4, 6, 4, 1}};
  EXPECT_EQ(generate(5), want);
}
