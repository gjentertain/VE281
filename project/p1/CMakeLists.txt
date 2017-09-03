CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project(p1)

include_directories(/usr/include/node)

add_executable(p1 answer/main.cpp answer/sort.cpp)
add_library(p1_sort benchmark/sort_wrapper.cpp answer/sort.cpp)


