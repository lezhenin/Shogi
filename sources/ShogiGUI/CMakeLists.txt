#Shogi

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(SOURCE_FILES
        main.cpp
        MainMenuGUI.cpp
        MainMenuGUI.h
        GameGUI.cpp
        GameGUI.h
        BoardFrame.cpp
        BoardFrame.h)


find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5LinguistTools REQUIRED )

qt5_add_resources(RESOURCE_ADDED resources/resources.qrc)

qt5_add_translation(TRANSLATION translation/translation_ru.ts)

add_executable(GUIApp ${SOURCE_FILES} ${RESOURCE_ADDED} ${TRANSLATION})

target_link_libraries(GUIApp Qt5::Core)
target_link_libraries(GUIApp Qt5::Widgets)
target_link_libraries(GUIApp ShogiCore)
