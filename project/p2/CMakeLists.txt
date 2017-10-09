CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project(p2)

include_directories(/usr/include/node)

add_executable(p2 answer/main.cpp answer/selection.cpp)
add_executable(p2_test answer/test.cpp answer/selection.cpp)
add_library(p2_selection benchmark/selection_wrapper.cpp answer/selection.cpp)

