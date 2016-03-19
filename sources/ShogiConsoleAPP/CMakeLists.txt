#Shogi
set(SOURCE_FILES
        main.cpp.cpp
        )
add_executable(APP main.cpp)
target_link_libraries(APP ShogiCore)