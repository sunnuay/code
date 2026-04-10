#include "feature.hpp"
#include <cstddef>
#include <expected>
#include <iostream>
#include <optional>
#include <print>
#include <ranges>
#include <string>
#include <vector>

std::expected<int, std::string> parse_number(const std::string &str) {
  if (str.empty())
    return std::unexpected("String is empty");
  try {
    return std::stoi(str);
  } catch (...) {
    return std::unexpected("Invalid number format");
  }
}

void cpp23() {
  std::cout << "--- cpp23 ---" << std::endl;
  auto result = parse_number("42");
  if (result.has_value()) {
    std::println("Parsed successfully: {}", result.value());
  } else {
    std::println("Error: {}", result.error());
  }

  std::vector<std::string> fruits = {"Apple", "Banana", "Cherry"};
  for (auto const &[index, fruit] : fruits | std::views::enumerate) {
    std::println("Fruit[{}] = {}", index, fruit);
  }

  std::optional<std::string> input = "hello";
  auto upper_length =
      input.transform([](const std::string &s) { return s.length(); }).or_else([]() -> std::optional<size_t> {
        return 0;
      });
  std::println("Length: {}", upper_length.value());
  std::cout << std::endl;
}

static Register r(cpp23);
