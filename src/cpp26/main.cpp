#include <iostream>
#include <map>
#include <string>

int main() {
  // 占位符
  std::map<int, std::string> my_map;
  auto [_, success1] = my_map.insert({1, "a"});
  auto [_, success2] = my_map.insert({1, "b"}); // 允许重定义
  if (success1 && !success2)
    std::cout << "Wildcard works!\n";

  // Pack Indexing
  auto get_second = []<typename... Ts>(Ts... args) {
    return args...[1]; // 直接返回第2个参数
  };
  std::cout << "Second arg is: " << get_second(10, 3.14, "hello") << "\n";
}
