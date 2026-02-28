#include <algorithm>
#include <concepts>
#include <format>
#include <iostream>
#include <span>
#include <string>
#include <vector>

import math;

// Concepts
template <typename T>
concept Addable = requires(T a, T b) {
  { a + b } -> std::same_as<T>;
};

template <Addable T> T add(T a, T b) { return a + b; }

// std::span
void process_data(std::span<int> data) {
  for (auto &item : data)
    item *= 2;
}

// 三路比较
struct Point {
  int x, y;
  auto operator<=>(const Point &) const = default; // 自动生成所有比较操作
};

int main() {
  std::cout << add(3, 4) << std::endl;

  // Concepts
  std::cout << "Addable: " << add(1, 2) << "\n";
  std::cout << "Addable: " << add(std::string("a"), std::string("b")) << "\n";
  // add("a", "b"); // 编译错误，因为 const char* 相加不返回 const char*

  // std::span
  std::vector<int> vec{1, 2, 3};
  int arr[] = {4, 5, 6};
  process_data(vec);
  process_data(arr);

  // std::format
  std::string msg =
      std::format("Hello {}! The answer is {:.2f}", "World", 3.14159);
  std::cout << msg << "\n";

  // 三路比较
  Point p1{1, 2}, p2{1, 3};
  if (p1 < p2)
    std::cout << "p1 is less than p2\n";

  // Ranges
  std::vector<int> nums{5, 2, 9, 1};
  std::ranges::sort(
      nums); // 直接传容器，代替 std::sort(nums.begin(), nums.end())
  for (int n : nums)
    std::cout << n << " ";
  std::cout << "\n";
}
