#include <expected>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

// 2. std::expected - ★★★★★ (现代错误处理，完美替代异常和 out 参数，类似 Rust 的
// Result)
enum class ErrorCode { NotFound, AccessDenied, InvalidInput };

std::expected<int, ErrorCode> divide(int a, int b) {
  if (b == 0)
    return std::unexpected(ErrorCode::InvalidInput);
  return a / b;
}

// 5. Deducing this (显式对象参数) - ★★★★☆ (消除 const 和非 const
// 函数的重复代码，极大简化 CRTP)
struct MyVector {
  std::vector<int> data_{1, 2, 3};

  // 以前需要写两个版本的 operator[] (一个 const，一个非 const)
  // 现在只需一个模板参数 self，自动推导调用者是 const 还是非 const！
  template <typename Self> auto &&operator[](this Self &&self, size_t index) {
    return std::forward<Self>(self).data_[index];
  }
};

int main() {
  std::cout << "--- C++23 Features ---\n";

  // 2. std::expected 测试
  auto res = divide(10, 2);
  if (res) { // operator bool 检查是否成功
    std::cout << "Result: " << *res << "\n";
  } else {
    std::cout << "Error occurred! Code: " << static_cast<int>(res.error())
              << "\n";
  }

  // 3. std::string::contains - ★★★★★ (终于不用写 str.find() !=
  // std::string::npos 了！)
  std::string_view text = "modern c++ is awesome";
  if (text.contains("c++")) {
    std::cout << "Found 'c++' in text!\n";
  }

  // 4. std::views::enumerate - ★★★★★ (类似 Python 的
  // enumerate，同时获取索引和值)
  std::vector<std::string> words{"zero", "one", "two"};
  for (auto const &[index, word] : std::views::enumerate(words)) {
    std::cout << "Index: " << index << ", Word: " << word << "\n";
  }

  // 5. Deducing this 测试
  MyVector vec;
  vec[0] = 10; // 调用非 const 版本

  const MyVector cvec;
  std::cout << "cvec[0]: " << cvec[0]
            << "\n"; // 自动调用 const 版本（返回 const int&）

  // 6. std::ranges::to - ★★★★☆ (将 Range 管道的结果直接转换回容器)
  auto even_nums =
      vec.data_ | std::views::filter([](int n) { return n % 2 == 0; }) |
      std::ranges::to<std::vector>(); // C++23 神器：流式处理完直接转 vector

  return 0;
}
