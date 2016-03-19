#ShogiCore

set(SOURCE_FILES
    constants.h
    enumirations.h
    Shogi.cpp
    Shogi.h
    ShogiGameAPI.h

    Model/Board.cpp
    Model/Board.h
    Model/AbstractBoard.h
    Model/Piece.cpp
    Model/Piece.h
    Model/Position.cpp
    Model/Position.h
    Model/Square.cpp
    Model/Square.h
    Model/SquareIsEmptyException.cpp
    Model/SquareIsEmptyException.h

    #Save.cpp Save.h
    Model/BoardMemento.cpp
    Model/BoardMemento.h)

add_library (ShogiCore STATIC ${SOURCE_FILES})


