#ShogiCore

set(SOURCE_FILES

        ShogiGameAPI.h

        Model/Board.cpp
        Model/Board.h
        Model/AbstractBoard.h
        Model/Piece.cpp
        Model/Piece.h
        Model/Square.cpp
        Model/Square.h
        Model/Exceptions/SquareIsEmptyException.h
        Model/Exceptions/BadPositionException.h
        Model/Exceptions/ModelException.h
        Model/BoardMemento.cpp
        Model/BoardMemento.h
        Model/AbstractBoardMemento.h
        Model/Position.cpp
        Model/Position.h

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
        GameLogic/TableOfDirections.h
        GameLogic/Exceptions/GameLogicException.h
        GameLogic/Exceptions/KingNotFoundException.h

        SaveAndLoad/GameLoader.cpp
        SaveAndLoad/GameLoader.h
        SaveAndLoad/AbstractGameLoader.h
        SaveAndLoad/Save.h
        SaveAndLoad/AbstractGameSaver.h
        SaveAndLoad/GameLoader.cpp
        SaveAndLoad/GameSaver.cpp
        SaveAndLoad/GameSaver.h

        Shogi.cpp
        Shogi.h)

add_library (ShogiCore STATIC ${SOURCE_FILES})


