#Shogi
set(SOURCE_FILES
        main.cpp
        Scenes/Scene.h
        Application.h
        Scenes/MainMenu.cpp
        Scenes/MainMenu.h
        Scenes/Game.cpp
        Scenes/Game.h
        GameApp.h
        Scenes/Help.cpp
        Scenes/Help.h)

add_executable(APP ${SOURCE_FILES})
target_link_libraries(APP ShogiCore)
#target_link_libraries(APP ShogiAI)