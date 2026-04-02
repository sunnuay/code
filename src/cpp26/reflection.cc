// g++ -std=c++26 -freflection reflection.cc

#include <meta>
#include <print>

using namespace std::meta;

template <typename T> void print(T const &t) {
  template for (constexpr auto e : define_static_array(nonstatic_data_members_of(^^T, access_context::current()))) {
    std::println(".{}={}", identifier_of(e), t.[:e:]);
  }
}

int main() {
  struct S {
    int a, b;
  };
  S s{97, 98};
  print(s);
}
