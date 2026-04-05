#include <print>

#if __has_include(<meta>)
#include <meta>
using namespace std::meta;
template <typename T> void print_all(T const &t) {
  template for (constexpr auto e : define_static_array(nonstatic_data_members_of(^^T, access_context::current()))) {
    std::println(".{}={}", identifier_of(e), t.[:e:]);
  }
}
#else
template <typename T> void print_all(T const &t) {
  auto const &[... e] = t;
  (std::println("{}", e), ...);
}
#endif

int main() {
  struct S {
    int a, b;
  } s{97, 98};
  print_all(s);
}
