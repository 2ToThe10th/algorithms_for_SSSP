cmake_minimum_required(VERSION 2.8)
project(SSSP)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")

add_subdirectory(googletest)
include_directories(googletest/googletest/include)

include_directories(src)
include_directories(test)

set(SOURCE_FILES src/main.cpp test/test.cpp src/DijkstraWithHeap.cpp src/DijkstraWithHeap.h src/SSSP.h src/BellmanFord.cpp src/BellmanFord.h src/SPFA.cpp src/SPFA.h src/AStar.cpp src/AStar.h src/DijkstraWithFibonacciHeap.cpp src/DijkstraWithFibonacciHeap.h src/AStarWithFibonacciHeap.cpp src/AStarWithFibonacciHeap.h)

add_executable(sssp ${SOURCE_FILES})
target_link_libraries(sssp gtest gtest_main)