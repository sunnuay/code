#include <iostream>
#include <memory>

struct Resource {
  void do_something() { std::cout << "Resource is working." << std::endl; }
};

int main() {
  auto adder = [](auto a, auto b) { return a + b; };
  auto sum_int = adder(1, 2);
  auto sum_double = adder(1.5, 2.3);
  auto sum_str = adder(std::string("a"), std::string("b"));

  auto p = std::make_unique<Resource>();
  auto worker_lambda = [ptr = std::move(p)]() { ptr->do_something(); };
  worker_lambda();
}
