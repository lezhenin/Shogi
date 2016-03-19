cmake_minimum_required(VERSION 2.8.12.2)
project(Shogi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(sources/ShogiCore)
add_subdirectory(sources/ShogiAI)
add_subdirectory(sources/ShogiCoreTest)


enable_testing()
add_test(NAME test COMMAND func_test)
