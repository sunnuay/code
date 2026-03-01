#include <iostream>
#include <memory>
#include <string>

class Resource {
public:
  void do_something() { std::cout << "Resource is working." << std::endl; }
};

int main() {
  // Generic Lambda
  // 允许在lambda参数中使用auto关键字，使其行为类似于模板函数，可以接收不同类型的参数并自动推导
  auto adder = [](auto a, auto b) { return a + b; };

  auto sum_int = adder(1, 2);
  auto sum_double = adder(1.5, 2.3);
  auto sum_str = adder(std::string("a"), std::string("b"));

  // std::make_unique
  // 补齐了C++11中缺失的make_unique，提供了异常安全的独占智能指针创建方式
  auto p = std::make_unique<Resource>();

  // Lambda Capture Initialization
  // 允许在lambda的捕获列表中进行变量的初始化或执行std::move，从而将仅限移动的类型（如unique_ptr）安全地传入lambda内部
  auto worker_lambda = [ptr = std::move(p)]() { ptr->do_something(); };

  worker_lambda();
}
