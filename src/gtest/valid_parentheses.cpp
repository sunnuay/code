#include <gtest/gtest.h>
#include <stack>
#include <string>
#include <string_view>

using namespace std;

bool is_valid(string_view text) {
  string_view left = "([{";
  string_view right = ")]}";
  stack<char> expect;
  for (char c : text) {
    if (left.contains(c)) {
      expect.push(right[left.find(c)]);
    } else if (!expect.empty() && expect.top() == c) {
      expect.pop();
    } else {
      return false;
    }
  }
  return expect.empty();
}

TEST(valid_parentheses, basic) {
  string text = "()";
  EXPECT_TRUE(is_valid(text));
}
