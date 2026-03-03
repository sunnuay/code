#include <iostream>
#include <map>
#include <vector>

std::optional<int> find_value(const std::vector<int> &vec, int target) {
  auto it = std::find(vec.begin(), vec.end(), target);
  if (it != vec.end())
    return *it;
  return std::nullopt;
}

void process_string(std::string_view str) {
  std::cout << "Processing: " << str << "\n";
}

int main() {
  process_string("hello");
  process_string(std::string("world"));

  std::map<std::string, int> scores{{"Alice", 95}, {"Bob", 87}};
  for (const auto &[name, score] : scores) {
    std::cout << name << ": " << score << "\n";
  }

  std::vector<int> numbers = {1, 2, 3, 4, 5};
  if (auto val = find_value(numbers, 3); val.has_value()) {
    std::cout << "Found value: " << *val << "\n";
  }
}
