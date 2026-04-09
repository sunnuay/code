#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace cpp11 {
struct Buffer {
  std::unique_ptr<int[]> data;
  Buffer() = default;
  Buffer(Buffer &&other) noexcept : data(std::move(other.data)) {}
  Buffer &operator=(Buffer &&other) noexcept {
    data = std::move(other.data);
    return *this;
  }
};

void run() {
  std::cout << "--- C++11 Demo ---" << std::endl;
  auto shared_buffer = std::make_shared<Buffer>();

  std::vector<int> nums{4, 1, 3, 2, 5, 7, 6};
  std::sort(nums.begin(), nums.end(), [](int a, int b) { return a > b; });
  int threshold = 5;
  auto greater_than = [threshold](int x) { return x > threshold; };
  auto count = std::count_if(nums.begin(), nums.end(), greater_than);

  std::vector<std::string> words{"C++11", "is", "awesome"};
  for (const auto &word : words) {
    std::cout << word << " ";
  }
  std::cout << "\nGreater than 5 count: " << count << std::endl << std::endl;
}
} // namespace cpp11
