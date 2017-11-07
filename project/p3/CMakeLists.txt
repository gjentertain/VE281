CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project(p3)

SET(CMAKE_CXX_STANDARD 14)
include_directories(/usr/include/node)

add_executable(p3 answer/main.cpp answer/binary_heap.h answer/unsorted_heap.h answer/fib_heap.h answer/priority_queue.h)
add_executable(p3_heap_test answer/test_heap.cpp)
add_library(p3_benchmark benchmark/queue_wrapper.cpp)
