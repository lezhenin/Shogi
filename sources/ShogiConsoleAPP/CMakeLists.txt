#Shogi
set(SOURCE_FILES
        main.cpp
        ConsoleGame.cpp
        ConsoleGame.h
        Commands/Command.h
        Commands/Move.h
        Commands/Pick.h
        Commands/UnPick.h
        Commands/Drop.h
        Commands/Exit.h)

add_executable(APP ${SOURCE_FILES})
target_link_libraries(APP ShogiCore)
#target_link_libraries(APP ShogiAI)