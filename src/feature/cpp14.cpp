#include <iostream>
#include <memory>
#include <string>
#include <utility>

namespace cpp14 {
struct Resource {
  void do_something() { std::cout << "Resource is working." << std::endl; }
};

void run() {
  std::cout << "--- C++14 Demo ---" << std::endl;
  auto adder = [](auto a, auto b) { return a + b; };
  auto sum_int = adder(1, 2);
  auto sum_double = adder(1.5, 2.3);
  auto sum_str = adder(std::string("a"), std::string("b"));

  std::cout << "Sum int: " << sum_int << ", double: " << sum_double << ", string: " << sum_str << std::endl;

  auto p = std::make_unique<Resource>();
  auto worker_lambda = [ptr = std::move(p)]() { ptr->do_something(); };
  worker_lambda();
  std::cout << std::endl;
}
} // namespace cpp14
