#include <print>
#include <tuple>

// Pack Indexing
// 允许直接使用类似数组下标的语法来访问可变参数模板中的特定类型或变量，彻底告别了过去为了获取参数包中第N个元素而编写的复杂递归解包或tuple转换代码
template <typename... Args> void print_first_and_last(Args... args) {
  constexpr auto last_idx = sizeof...(Args) - 1;
  std::println("First: {}, Last: {}", args...[0], args...[last_idx]);
}

int main() {
  // Placeholder _
  // 原生支持了单下划线作为忽略变量的占位符，在解构绑定或接收互斥锁等不需要实际访问变量名的情况下，可以直接用
  // _ 避免编译器产生“变量未使用”的警告，且可以多次重复使用
  auto [x, _, z] = std::make_tuple(1, "ignored", 3.14);
  std::println("x: {}, z: {}", x, z);

  [[maybe_unused]] auto _ = 42;
  [[maybe_unused]] auto _ = "another ignored value";

  print_first_and_last(10, 20, 30, "Hello");

  // constexpr string in static_assert
  // 允许在静态断言中使用在编译期动态生成的格式化字符串，从而能在触发编译错误时，提供包含具体类型或数值的高度定制化且极具可读性的错误提示信息
  constexpr int buffer_size = 256;
  // static_assert(buffer_size >= 512, std::format("Buffer size {} is too small,
  // must be >= 512", buffer_size));
  // 若放开上方注释，编译器将在编译失败时直接输出动态拼接的具体数值错误信息
}
