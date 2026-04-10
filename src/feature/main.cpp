#include "feature.hpp"

int main() {
  for (auto f : features()) {
    f();
  }
}
