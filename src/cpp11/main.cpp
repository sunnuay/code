#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

// 移动语义
class Buffer {
  std::unique_ptr<int[]> data;

public:
  Buffer() : data(new int[10]) {}

  // 移动构造
  Buffer(Buffer &&other) noexcept : data(std::move(other.data)) {
    std::cout << "Move Constructor called.\n";
  }

  // 移动赋值
  Buffer &operator=(Buffer &&other) noexcept {
    if (this != &other) {
      data = std::move(other.data);
      std::cout << "Move Assignment called.\n";
    }
    return *this;
  }
};

// override 与 enum class
enum class Status { OK, Error }; // 强类型枚举，不会隐式转换为 int，防止命名冲突

class Base {
public:
  virtual void doWork() const { std::cout << "Base work\n"; }
  virtual ~Base() = default;
};

class Derived : public Base {
public:
  // 明确声明重写，如果函数签名写错（比如漏了 const），编译器会报错
  void doWork() const override { std::cout << "Derived work\n"; }
};

int main() {
  // auto &
  std::vector<std::string> words{"hello", "world"};
  for (const auto &word : words) {
    std::cout << word << " ";
  }
  std::cout << "\n";

  // lambda 表达式
  std::vector<int> nums{4, 1, 3, 2, 5};
  // 降序排序
  std::sort(nums.begin(), nums.end(), [](int a, int b) { return a > b; });

  int threshold = 2;
  // 捕获外部变量 threshold
  auto greater_than = [threshold](int x) { return x > threshold; };
  auto count = std::count_if(nums.begin(), nums.end(), greater_than);
  std::cout << "Count > 2: " << count << "\n";

  // 智能指针
  auto shared = std::make_shared<Base>();
  std::unique_ptr<Base> unique(new Derived()); // C++11 还没有 make_unique
  unique->doWork();

  // 移动语义
  Buffer b1;
  Buffer b2 = std::move(b1); // 触发移动构造

  // enum class
  Status s = Status::OK;
  if (s == Status::OK)
    std::cout << "Status is OK\n";
}
