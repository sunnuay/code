#include <print>

template <typename... Args> void print_first_and_last(Args... args) {
  constexpr auto last_idx = sizeof...(Args) - 1;
  std::println("First: {}, Last: {}", args...[0], args...[last_idx]);
}

int main() {
  auto [_, _, z] = std::make_tuple(1, 2, 3);
  std::println("z: {}", z);

  print_first_and_last("a", "b", "c");
}
