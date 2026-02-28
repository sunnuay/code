#include <expected>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

// std::expected
enum class ErrorCode { NotFound, AccessDenied, InvalidInput };

std::expected<int, ErrorCode> divide(int a, int b) {
  if (b == 0)
    return std::unexpected(ErrorCode::InvalidInput);
  return a / b;
}

// Deducing this
struct MyVector {
  std::vector<int> data_{1, 2, 3};
  // 以前需要写两个版本的 operator[] (一个 const，一个非 const)
  // 现在只需一个模板参数 self，自动推导调用者是 const 还是非 const
  template <typename Self> auto &&operator[](this Self &&self, size_t index) {
    return std::forward<Self>(self).data_[index];
  }
};

int main() {
  // std::expected
  auto res = divide(10, 2);
  if (res) { // operator bool 检查是否成功
    std::cout << "Result: " << *res << "\n";
  } else {
    std::cout << "Error occurred! Code: " << static_cast<int>(res.error())
              << "\n";
  }

  // std::string::contains
  std::string_view text = "modern c++ is awesome";
  if (text.contains("c++")) {
    std::cout << "Found 'c++' in text!\n";
  }

  // std::views::enumerate
  std::vector<std::string> words{"zero", "one", "two"};
  for (auto const &[index, word] : std::views::enumerate(words)) {
    std::cout << "Index: " << index << ", Word: " << word << "\n";
  }

  // Deducing this
  MyVector vec;
  vec[0] = 10; // 调用非 const 版本

  const MyVector cvec;
  std::cout << "cvec[0]: " << cvec[0]
            << "\n"; // 自动调用 const 版本（返回 const int&）

  // std::ranges::to
  auto even_nums = vec.data_ |
                   std::views::filter([](int n) { return n % 2 == 0; }) |
                   std::ranges::to<std::vector>(); // 流式处理完直接转 vector
}
