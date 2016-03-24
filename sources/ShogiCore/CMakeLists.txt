#ShogiCore

set(SOURCE_FILES
    Shogi.cpp
    Shogi.h
    ShogiGameAPI.h
    Position.cpp
    Position.h
    BadPositionException.cpp
    BadPositionException.h

    GameSituations/GameSituation.h
    GameSituations/Shah.h
    GameSituations/Shah.cpp
    GameSituations/Mate.cpp
    GameSituations/Mate.h
    GameSituations/PromotionIsAvailable.cpp
    GameSituations/PromotionIsAvailable.h

    Model/Board.cpp
    Model/Board.h
    Model/AbstractBoard.h
    Model/Piece.cpp
    Model/Piece.h
    Model/Square.cpp
    Model/Square.h
    Model/SquareIsEmptyException.cpp
    Model/SquareIsEmptyException.h
    Model/BoardMemento.cpp
    Model/BoardMemento.h )

add_library (ShogiCore STATIC ${SOURCE_FILES})


