#ShogiCore

set(SOURCE_FILES

        API/GameAPI.h

        Model/Board.cpp
        Model/Board.h
        Model/AbstractBoard.h
        Model/Piece.cpp
        Model/Piece.h
        Model/Square.cpp
        Model/Square.h
        Model/Exceptions/BadPositionException.h
        Model/Exceptions/ModelException.h
        Model/BoardMemento.cpp
        Model/BoardMemento.h
        Model/AbstractBoardMemento.h
        Model/Position.cpp
        Model/Position.h
        Model/Player.h
        Model/Player.cpp

        GameLogic/GameLogic.cpp
        GameLogic/GameLogic.h
        GameLogic/Direction.h
        GameLogic/GameSituations/GameSituation.h
        GameLogic/GameSituations/Shah.h
        GameLogic/GameSituations/Mate.h
        GameLogic/GameSituations/PromotionIsAvailable.h
        GameLogic/AbstractGameLogic.h
        GameLogic/TableOfDirections.h
        GameLogic/Exceptions/GameLogicException.h
        GameLogic/Exceptions/KingNotFoundException.h

        SaveAndLoad/GameLoader.cpp
        SaveAndLoad/GameLoader.h
        SaveAndLoad/Simple/SimpleSave.h
        SaveAndLoad/GameLoader.cpp
        SaveAndLoad/GameSaver.cpp
        SaveAndLoad/GameSaver.h
        SaveAndLoad/SaveWriter.h
        SaveAndLoad/SaveReader.h
        SaveAndLoad/Block.h
        SaveAndLoad/JSON/JSONSaveManager.cpp
        SaveAndLoad/JSON/JSONSaveManager.h
        SaveAndLoad/Simple/SimpleSaveManager.cpp
        SaveAndLoad/Simple/SimpleSaveManager.h

        API/Shogi.cpp
        API/Shogi.h
        API/Exceptions/GameProcessException.h
        API/Exceptions/BadMoveException.h
        API/Exceptions/BadPickException.h
        API/Exceptions/BadDropException.h
        API/Exceptions/BadPromoteException.h Model/Exceptions/PieceIsNotOnBoardException.h AI/AI.cpp AI/AI.h)

add_library (ShogiCore ${SOURCE_FILES})




