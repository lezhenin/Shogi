cmake_minimum_required(VERSION 2.8.12.2)
project(Shogi)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -std=c++11 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -fprofile-arcs -ftest-coverage -O0 -o --coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

link_libraries(gcov)
add_subdirectory(sources)



