#Shogi
set(SOURCE_FILES
        main.cpp.cpp
        )
add_executable(APP main.cpp ConsoleGame.cpp ConsoleGame.h)
target_link_libraries(APP ShogiCore)
target_link_libraries(APP ShogiAI)