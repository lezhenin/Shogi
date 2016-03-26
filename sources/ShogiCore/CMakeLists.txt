#ShogiCore

set(SOURCE_FILES
        Shogi.cpp
        Shogi.h
        ShogiGameAPI.h
        Model/Position.cpp
        Model/Position.h
        Model/BadPositionException.cpp
        Model/BadPositionException.h
        GameLogic/ShogiGameLogic.cpp
        GameLogic/ShogiGameLogic.h
        GameLogic/Direction.h
        GameLogic/GameSituations/GameSituation.h
        GameLogic/GameSituations/Shah.h
        GameLogic/GameSituations/Shah.cpp
        GameLogic/GameSituations/Mate.cpp
        GameLogic/GameSituations/Mate.h
        GameLogic/GameSituations/PromotionIsAvailable.cpp
        GameLogic/GameSituations/PromotionIsAvailable.h
        GameLogic/AbstractShogiGameLogic.h
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
        Model/BoardMemento.h
        Model/AbstractBoardMemento.h)

add_library (ShogiCore STATIC ${SOURCE_FILES})


