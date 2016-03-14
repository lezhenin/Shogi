cmake_minimum_required(VERSION 3.3)
project(Shogi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(sources/Shogi/ShogiCore)
add_subdirectory(sources/Shogi/ShogiAI)
add_subdirectory(sources/Shogi/ShogiCoreTest)


enable_testing()
add_test(NAME test COMMAND func_test)
