#include <concepts>
#include <format>
#include <iostream>
#include <span>
#include <string>
#include <vector>

// Concepts
// 提供了一种类型约束机制，在编译期检查模板类型是否满足特定条件，不满足时会给出极具可读性的编译错误提示，取代了难懂的SFINAE
template <typename T>
concept Addable = requires(T a, T b) {
  { a + b } -> std::same_as<T>;
};

template <Addable T> T add(T a, T b) { return a + b; }

// std::span
// 提供了一个轻量级的、无所有权的连续内存视图，统一了原生数组、std::vector和std::array的参数传递方式，包含边界信息且不发生拷贝
void process_data(std::span<int> data) {
  for (auto &item : data) {
    item *= 2;
  }
}

// Three-way Comparison (<=>)
// 也被称为“飞船运算符”，只需一行默认实现即可由编译器自动生成所有六个关系比较运算符（<,
// <=, >, >=, ==, !=），大幅减少模板代码
struct Point {
  int x, y;
  auto operator<=>(const Point &) const = default;
};

int main() {
  auto res = add(1, 2);
  // add("a", "b"); // 若取消注释将直接触发Concepts定义的编译错误

  std::vector<int> vec{1, 2, 3};
  int arr[] = {4, 5, 6};
  process_data(vec);
  process_data(arr);

  Point p1{1, 2}, p2{1, 3};
  if (p1 < p2) {
    std::cout << "p1 is strictly less than p2\n";
  }

  // std::format
  // 结合了printf的性能优势和C++流的安全性与类型检查，使用大括号作为占位符，提供了现代化的字符串格式化体验
  std::string msg =
      std::format("Hello {}! The answer is {:.2f}", "World", 3.14159);
  std::cout << msg << "\n";
}
