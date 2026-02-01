# cmake -S . -B build -D src=<folder>
# cmake --build build --target run
cmake_minimum_required(VERSION 4.2)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
project(code)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(GLOB sources CONFIGURE_DEPENDS "${src}/*.c" "${src}/*.cpp")
add_executable(main ${sources})
add_custom_target(run COMMAND main DEPENDS main)
