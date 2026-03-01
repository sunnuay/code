#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Move Semantics
// 实现移动构造和移动赋值函数，通过无锁的资源转移避免深拷贝开销，提升性能
class Buffer {
  std::unique_ptr<int[]> data;

public:
  Buffer() = default;

  Buffer(Buffer &&other) noexcept : data(std::move(other.data)) {}

  Buffer &operator=(Buffer &&other) noexcept {
    data = std::move(other.data);
    return *this;
  }
};

int main() {
  // Smart Pointers & auto
  // 使用auto自动推导类型，结合make_unique和make_shared进行独占或共享的自动内存管理，避免内存泄漏
  auto unique_buffer = std::make_unique<Buffer>();
  auto shared_buffer = std::make_shared<Buffer>();
  auto i = 42;
  auto &ref = i;

  std::vector<int> nums{4, 1, 3, 2, 5, 7, 6};

  // Lambda Expressions
  // 支持就地编写匿名函数，极大地简化了配合STL算法（如排序、条件统计）时的代码编写逻辑
  std::sort(nums.begin(), nums.end(), [](int a, int b) { return a > b; });

  int threshold = 5;
  auto greater_than = [threshold](int x) { return x > threshold; };
  auto count = std::count_if(nums.begin(), nums.end(), greater_than);

  std::vector<std::string> words{"C++11", "is", "awesome"};

  // Range-based for loop
  // 隐藏了迭代器的细节，提供了一种极为简洁、安全的方式来遍历容器中的所有元素
  for (const auto &word : words) {
    std::cout << word << " ";
  }
}
