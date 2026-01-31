# cmake -S . -B build -D src=<folder>
# cmake --build build --target run
cmake_minimum_required(VERSION 4.2)
project(code)
file(GLOB sources CONFIGURE_DEPENDS "${src}/*.c" "${src}/*.cpp")
add_executable(main ${sources})
target_compile_features(main PRIVATE cxx_std_23)
add_custom_target(run COMMAND main DEPENDS main)
