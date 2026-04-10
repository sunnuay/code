#include "feature.hpp"
#include <iostream>

import cpp20;

struct Point {
  int x, y;
  auto operator<=>(const Point &) const = default;
};

void cpp20() {
  std::cout << "--- cpp20 ---" << std::endl;

  auto res = add(1, 1.1);
  std::cout << "1 + 1.1 = " << res << std::endl;

  Point p1{1, 2}, p2{1, 3};
  if (p1 < p2) {
    std::cout << "p1 is strictly less than p2" << std::endl;
  }

  std::cout << std::endl;
}

static Register r(cpp20);
