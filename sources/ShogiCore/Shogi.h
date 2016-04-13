#ifndef SHOGI_SHOGI_H
#define SHOGI_SHOGI_H

#include <stack>
#include "GameLogic/GameSituations/PromotionIsAvailable.h"
#include "GameLogic/GameSituations/Shah.h"
#include "GameLogic/GameSituations/Mate.h"
#include "ShogiGameAPI.h"
#include "GameLogic/ShogiGameLogic.h"
#include "SaveAndLoad/GameLoader.h"
#include "SaveAndLoad/GameSaver.h"

class Shogi: public ShogiGameAPI
{

public:

    Shogi();
    virtual void initGame() override;
    virtual Player getCurrentPlayer() const override;
    virtual void pickPiece(const Position &position) override;
    virtual void unPickPiece() override;
    virtual void movePiece(const Position &position) override;
    virtual void promotePiece(const Position &position) override;
    virtual void dropPiece(const PieceType pieceType, const Position &position) override;
    virtual void undo() override;
    virtual void redo() override;
    virtual AbstractBoard &getBoard() const override;
    virtual ListOfGameSituations& getGameSituation() override;
    virtual ~Shogi();

private:
    AbstractBoard* board;
    AbstractShogiGameLogic* gameLogic;
    GameLoader* gameLoader;
    GameSaver* gameSaver;
    ListOfGameSituations gameSituations;
    std::stack<AbstractBoardMemento*> toUndo;
    std::stack<AbstractBoardMemento*> toRedo;
    Piece *pickedPiece = nullptr;
    Player currentPlayer = Sente;

    void clearToUndo();
    void clearToRedo();

    Player transformPlayer(Player player) const;
};


#endif //SHOGI_SHOGI_H
