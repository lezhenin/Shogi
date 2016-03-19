#Shogi

add_subdirectory(ShogiCore)
add_subdirectory(ShogiAI)
add_subdirectory(ShogiCoreTest)


enable_testing()
add_test(NAME test COMMAND func_test)
