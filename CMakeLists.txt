cmake_minimum_required(VERSION 2.8.12.2)
project(Shogi)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_definitions(-fprofile-arcs -ftest-coverage --coverage)
link_libraries(gcov)
add_subdirectory(sources)



