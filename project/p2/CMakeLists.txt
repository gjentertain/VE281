CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project(p2)

include_directories(/usr/include/node)

add_executable(p2 answer/main.cpp answer/selection.cpp)


