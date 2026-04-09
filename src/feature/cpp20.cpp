#include <concepts>
#include <span>
#include <vector>
#include <iostream>

import test;

namespace cpp20 {
template <typename T>
concept Addable = requires(T a, T b) {
  { a + b } -> std::same_as<T>;
};
template <Addable T> T add(T a, T b) { return a + b; }

void process_data(std::span<int> data) {
  for (auto &item : data) {
    item *= 2;
  }
}

struct Point {
  int x, y;
  auto operator<=>(const Point &) const = default;
};

void run() {
  std::cout << "--- C++20 Demo ---" << std::endl;
  auto res = add(1, 2);
  std::cout << "Addable concept demo: 1 + 2 = " << res << std::endl;

  std::vector<int> vec{1, 2, 3};
  int arr[] = {4, 5, 6};
  process_data(vec);
  process_data(arr);
  std::cout << "Span demo (vector): ";
  for(auto v : vec) std::cout << v << " ";
  std::cout << "\nSpan demo (array): ";
  for(auto v : arr) std::cout << v << " ";
  std::cout << std::endl;

  Point p1{1, 2}, p2{1, 3};
  if (p1 < p2) {
    print("p1 is strictly less than p2\n");
  }
  std::cout << std::endl;
}
} // namespace cpp20
