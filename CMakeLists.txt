cmake_minimum_required(VERSION 3.3)
project(Shogi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    sources/Shogi/ShogiAI/shogiai.cpp
    sources/Shogi/ShogiAI/shogiai.h
    sources/Shogi/ShogiCore/Board.cpp
    sources/Shogi/ShogiCore/Board.h
    sources/Shogi/ShogiCore/BoardInterface.h
    sources/Shogi/ShogiCore/constants.h
    sources/Shogi/ShogiCore/enumirations.h
    sources/Shogi/ShogiCore/Piece.cpp
    sources/Shogi/ShogiCore/Piece.h
    sources/Shogi/ShogiCore/Position.cpp
    sources/Shogi/ShogiCore/Position.h
    sources/Shogi/ShogiCore/Shogi.cpp
    sources/Shogi/ShogiCore/Shogi.h
    sources/Shogi/ShogiCore/ShogiAPI.cpp
    sources/Shogi/ShogiCore/ShogiAPI.h
    sources/Shogi/ShogiCore/Square.cpp
    sources/Shogi/ShogiCore/Square.h
    sources/Shogi/ShogiCore/SquareIsEmptyException.cpp
    sources/Shogi/ShogiCore/SquareIsEmptyException.h
    sources/Shogi/ShogiCoreTest/tst_ShogiCoreTest.cpp
)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package( Qt5Core REQUIRED )
find_package( Qt5Test REQUIRED )
add_executable(Shogi ${SOURCE_FILES})
target_link_libraries(Shogi Qt5::Core)
target_link_libraries(Shogi Qt5::Test)

