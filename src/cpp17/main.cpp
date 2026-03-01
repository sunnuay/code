#include <algorithm>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

// std::optional
// 用于表示一个可能存在也可能不存在的值，替代了以往使用魔术数字（如-1）或空指针来表示查找失败的做法，访问更加安全
std::optional<int> find_value(const std::vector<int> &vec, int target) {
  auto it = std::find(vec.begin(), vec.end(), target);
  if (it != vec.end())
    return *it;
  return std::nullopt;
}

// std::string_view
// 提供对字符串的只读视图，不发生内存分配和拷贝，可以同时接收C风格字符串和std::string，极大提升了字符串传递的性能
void process_string(std::string_view str) {
  std::cout << "Processing: " << str << "\n";
}

int main() {
  process_string("hello");
  process_string(std::string("world"));

  std::map<std::string, int> scores{{"Alice", 95}, {"Bob", 87}};

  // Structured Binding
  // 允许直接将元组、pair或结构体的数据解包到命名变量中，在遍历map或处理多返回值时代码更加直观清晰
  for (const auto &[name, score] : scores) {
    std::cout << name << ": " << score << "\n";
  }

  std::vector<int> numbers = {1, 2, 3, 4, 5};

  // if/switch with Initialization
  // 允许在控制流语句中直接进行变量的初始化，将变量的作用域严格限制在if块内部，避免了命名空间污染
  if (auto val = find_value(numbers, 3); val.has_value()) {
    std::cout << "Found value: " << *val << "\n";
  }
}
