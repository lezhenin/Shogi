#ShogiCoreTest
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(func_test tst_ShogiCoreFuncTest.cpp)
add_executable(module_test tst_ShogiCoreModuleTest.cpp)

find_package( Qt5Core REQUIRED )
find_package( Qt5Test REQUIRED )

target_link_libraries(func_test ShogiCore)
target_link_libraries(func_test Qt5::Core)
target_link_libraries(func_test Qt5::Test)

target_link_libraries(module_test ShogiCore)
target_link_libraries(module_test Qt5::Core)
target_link_libraries(module_test Qt5::Test)