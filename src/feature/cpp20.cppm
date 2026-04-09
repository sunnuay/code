module;

#include <format>
#include <iostream>

export module cpp20;

export template <typename... Args> void print(std::format_string<Args...> fmt, Args &&...args) {
  std::cout << std::format(fmt, std::forward<Args>(args)...);
}
