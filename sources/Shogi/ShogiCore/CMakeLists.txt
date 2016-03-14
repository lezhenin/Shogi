#ShogiCore

set(SOURCE_FILES
    Board.cpp
    Board.h
    BoardInterface.h
    constants.h
    enumirations.h
    Piece.cpp
    Piece.h
    Position.cpp
    Position.h
    Shogi.cpp
    Shogi.h
    ShogiAPI.cpp
    ShogiAPI.h
    Square.cpp
    Square.h
    SquareIsEmptyException.cpp
    SquareIsEmptyException.h
)

add_library (ShogiCore STATIC ${SOURCE_FILES})


