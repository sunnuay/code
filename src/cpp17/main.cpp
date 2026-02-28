#include <algorithm>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

// std::optional
std::optional<int> find_value(const std::vector<int> &vec, int target) {
  auto it = std::find(vec.begin(), vec.end(), target);
  if (it != vec.end())
    return *it;
  return std::nullopt;
}

// std::string_view
void process_string(std::string_view str) {
  if (str.length() >= 4 && str.substr(0, 4) == "http") {
    std::cout << "Valid URL: " << str << "\n";
  }
}

// constexpr if
template <typename T> void print_type_info(const T &val) {
  if constexpr (std::is_integral_v<T>) {
    std::cout << val << " is integral\n";
  } else {
    std::cout << val << " is not integral\n";
  }
}

int main() {
  // 结构化绑定
  std::map<std::string, int> scores{{"Alice", 95}, {"Bob", 87}};
  for (const auto &[name, score] : scores) { // 优雅地解包
    std::cout << name << ": " << score << "\n";
  }

  // std::optional
  if (auto val = find_value({1, 2, 3}, 2)) {
    std::cout << "Found: " << *val << "\n";
  }

  // std::string_view
  process_string("https://example.com"); // 从 const char* 构造 (零拷贝)
  std::string s = "http://test.com";
  process_string(s); // 从 std::string 构造 (零拷贝)

  // 带初始化的 if/switch
  if (auto it = scores.find("Alice"); it != scores.end()) {
    std::cout << "Alice's score: " << it->second << "\n";
    // it 的作用域仅限于 if 块内，非常干净
  }

  // constexpr if
  print_type_info(42);
  print_type_info(std::string("text"));
}
