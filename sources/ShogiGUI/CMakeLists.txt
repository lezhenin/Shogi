#Shogi

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(SOURCE_FILES
        main.cpp
        MainMenuG.cpp MainMenuG.h)


find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )

qt5_add_resources(RESOURCE_ADDED resources/resources.qrc)

add_executable(GUIApp ${SOURCE_FILES} ${RESOURCE_ADDED})

target_link_libraries(GUIApp Qt5::Core)
target_link_libraries(GUIApp Qt5::Widgets)