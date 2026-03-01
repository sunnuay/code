#include <expected>
#include <optional>
#include <print>
#include <ranges>
#include <string>
#include <vector>

// std::expected
// 提供了一种无需抛出异常即可处理错误的现代化方式，它要么包含一个期望的返回值，要么包含一个错误对象，非常适合在性能敏感或禁用异常的场景下替代传统的错误码
std::expected<int, std::string> parse_number(const std::string &str) {
  if (str.empty())
    return std::unexpected("String is empty");
  try {
    return std::stoi(str);
  } catch (...) {
    return std::unexpected("Invalid number format");
  }
}

// Deducing this
// 允许将this作为显式参数传递给成员函数，从而极大简化了CRTP（奇异递归模板模式）的编写，消除了重复的const和非const重载，并且允许lambda表达式轻松实现自递归
struct TreeNode {
  std::vector<TreeNode> children;

  template <typename Self> void traverse(this Self &&self) {
    std::println("Visiting node...");
    for (auto &&child : self.children) {
      child.traverse();
    }
  }
};

int main() {
  // std::print / std::println
  // 终于在标准库中引入了原生的格式化打印函数，完美替代了std::cout和std::format的组合，不仅语法更加简洁，而且编译速度和运行期性能都得到了大幅提升
  std::println("Welcome to C++{}!", 23);

  auto result = parse_number("42");
  if (result.has_value()) {
    std::println("Parsed successfully: {}", result.value());
  } else {
    std::println("Error: {}", result.error());
  }

  std::vector<std::string> fruits = {"Apple", "Banana", "Cherry"};

  // Ranges Improvements
  // 进一步完善了范围库，引入了类似Python的enumerate功能，可以在基于范围的for循环中同时且优雅地获取当前元素的索引和引用
  for (auto const &[index, fruit] : fruits | std::views::enumerate) {
    std::println("Fruit[{}] = {}", index, fruit);
  }

  std::optional<std::string> input = "hello";

  // Monadic Operations for std::optional
  // 为optional引入了and_then,
  // transform和or_else等链式调用方法，使得处理可能为空的值时不再需要频繁写if判断，逻辑代码更加流畅连贯
  auto upper_length =
      input.transform([](const std::string &s) { return s.length(); })
          .or_else([]() -> std::optional<size_t> { return 0; });

  std::println("Length: {}", upper_length.value());
}
