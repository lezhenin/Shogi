cmake_minimum_required(VERSION 2.8.12.2)
project(Shogi)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fprofile-arcs -ftest-coverage --coverage")
add_subdirectory(sources)



