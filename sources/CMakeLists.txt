#Shogi
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -std=c++11 -std=gnu++11 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -std=gnu++11 -fprofile-arcs -ftest-coverage -O0 -o --coverage")
add_subdirectory(ShogiCore)
add_subdirectory(ShogiAI)
add_subdirectory(ShogiCoreTest)
add_subdirectory(ShogiConsoleAPP)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -std=c++11 -std=gnu++11 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -std=gnu++11 -fprofile-arcs -ftest-coverage -O0 -o --coverage")
