#include "cpp_standards.hpp"
#include <iostream>

int main() {
  std::cout << "Starting C++ Standards Demo Program\n" << std::endl;
  
  cpp11::run();
  cpp14::run();
  cpp17::run();
  cpp20::run();
  cpp23::run();
  cpp26::run();
  
  std::cout << "All demos finished." << std::endl;
  return 0;
}
