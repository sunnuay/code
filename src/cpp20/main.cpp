#include <concepts>
#include <span>
#include <vector>

import test;

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

int main() {
  auto res = add(1, 2);

  std::vector<int> vec{1, 2, 3};
  int arr[] = {4, 5, 6};
  process_data(vec);
  process_data(arr);

  Point p1{1, 2}, p2{1, 3};
  if (p1 < p2) {
    print("p1 is strictly less than p2");
  }
}
