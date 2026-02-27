#include <iostream>
#include <map>
#include <string>

int main() {
  std::cout << "--- C++26 Features (Preview) ---\n";

  // 1. 占位符 `_` (Wildcard) - ★★★★★
  // 终于！在 C++26 中，你可以多次使用 `_` 作为变量名来丢弃不需要的返回值，
  // 再也不用写难看的 [[maybe_unused]] dummy_var 了。
  std::map<int, std::string> my_map;

  // 插入数据，只关心是否插入成功，不关心 iterator
  auto [_, success1] = my_map.insert({1, "a"});
  auto [_, success2] = my_map.insert({1, "b"}); // C++26 允许重定义 `_`
  if (success1 && !success2)
    std::cout << "Wildcard works!\n";

  // 3. Pack Indexing (参数包索引) - ★★★★☆
  // 模板元编程的救星：以前想获取可变参数包里的第 N 个类型/值，要写复杂的递归或
  // tuple。 现在直接用 `Ts...[N]` 和 `args...[N]`。
  auto get_second = []<typename... Ts>(Ts... args) {
    return args...[1]; // 直接返回第2个参数
  };
  std::cout << "Second arg is: " << get_second(10, 3.14, "hello") << "\n";

  return 0;
}
