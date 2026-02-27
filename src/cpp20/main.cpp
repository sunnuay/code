#include <algorithm>
#include <concepts>
#include <format>
#include <iostream>
#include <span>
#include <string>
#include <vector>

import math;

// 1. Concepts - ★★★★★
template <typename T>
concept Addable = requires(T a, T b) {
  { a + b } -> std::same_as<T>;
};

template <Addable T> T add(T a, T b) { return a + b; }

// 2. std::span - ★★★★★
void process_data(std::span<int> data) {
  for (auto &item : data)
    item *= 2;
}

// 4. 三路比较 (<=>) - ★★★★☆
struct Point {
  int x, y;
  auto operator<=>(const Point &) const = default; // 自动生成所有比较操作
};

int main() {
  std::cout << add(3, 4) << std::endl;

  std::cout << "--- C++20 Features ---\n";

  // 1. Concepts 测试
  std::cout << "Addable: " << add(1, 2) << "\n";
  std::cout << "Addable: " << add(std::string("a"), std::string("b")) << "\n";
  // add("a", "b"); // ❌ 编译错误，因为 const char* 相加不返回 const char*

  // 2. std::span 测试 (统一了数组和 vector 的传递)
  std::vector<int> vec{1, 2, 3};
  int arr[] = {4, 5, 6};
  process_data(vec); // ✅
  process_data(arr); // ✅

  // 3. std::format - ★★★★★ (注意：需 GCC 13+ 或 Clang 14+ 或 MSVC)
  std::string msg =
      std::format("Hello {}! The answer is {:.2f}", "World", 3.14159);
  std::cout << msg << "\n";

  // 4. 三路比较测试
  Point p1{1, 2}, p2{1, 3};
  if (p1 < p2)
    std::cout << "p1 is less than p2\n";

  // 5. 【补充】Ranges - ★★★★★ (告别繁琐的 begin()/end())
  std::vector<int> nums{5, 2, 9, 1};
  std::ranges::sort(
      nums); // 直接传容器，代替 std::sort(nums.begin(), nums.end())
  for (int n : nums)
    std::cout << n << " ";
  std::cout << "\n";

  return 0;
}
