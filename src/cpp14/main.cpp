#include <iostream>
#include <memory>
#include <string>

// 用于测试的桩类
struct MyClass {
  int a;
  double b;
  MyClass(int a, double b) : a(a), b(b) {}
  void print() { std::cout << "MyClass: " << a << ", " << b << "\n"; }
};

struct Resource {
  void do_something() { std::cout << "Resource is doing something.\n"; }
};

int main() {
  std::cout << "--- C++14 Features ---\n";

  // 1. 泛型 lambda - ★★★★★ (勘误：修复了缺少的 [] 和 ())
  auto adder = [](auto a, auto b) { return a + b; };
  std::cout << "adder(1, 2): " << adder(1, 2) << "\n";
  std::cout << "adder(1.5, 2.3): " << adder(1.5, 2.3) << "\n";
  std::cout << "adder string: " << adder(std::string("a"), "b") << "\n";

  // 2. std::make_unique - ★★★★★ (完美对称 make_shared，避免 new 的异常风险)
  auto ptr = std::make_unique<MyClass>(10, 3.14);
  ptr->print();

  // 3. lambda 捕获初始化 - ★★★★☆ (主要用于把 unique_ptr move 进 lambda)
  auto p = std::make_unique<Resource>();
  auto lambda = [res_ptr =
                     std::move(p)]() { // 移动捕获，将 p 的所有权转移给 res_ptr
    res_ptr->do_something();
  };
  lambda();
  // 此时外面的 p 已经是 nullptr 了

  return 0;
}
