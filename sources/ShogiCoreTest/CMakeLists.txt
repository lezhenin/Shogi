#ShogiCoreTest
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fprofile-arcs -fPIC -ftest-coverage -O0 -o --coverage")

set(SOURCE_FILES
        tst_ShogiCoreTest.cpp
        )

add_executable(func_test ${SOURCE_FILES})

find_package( Qt5Core REQUIRED )
find_package( Qt5Test REQUIRED )

target_link_libraries(func_test ShogiCore)
target_link_libraries(func_test ShogiAI)
target_link_libraries(func_test Qt5::Core)
target_link_libraries(func_test Qt5::Test)
target_link_libraries(func_test gcov)