cmake_minimum_required(VERSION 3.10)

project(advent2021)
set(simple_VERSION_MAJOR 1)
set(simple_VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(prog)
add_subdirectory(tests)

enable_testing()
