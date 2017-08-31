CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project(p1)

add_executable(p1 answer/main.cpp answer/sort.cpp test/main.cpp)

add_executable(p1_test test/main.cpp answer/sort.cpp)
add_executable(p1_generate test/generate.cpp)
