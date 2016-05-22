cmake_minimum_required(VERSION 2.8.12.2)
project(Shogi)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -fprofile-arcs -ftest-coverage -O0 -o --coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if (CMAKE_BUILD_TYPE=Debug)
link_libraries(gcov)
endif()

add_subdirectory(sources)
add_subdirectory(report)



