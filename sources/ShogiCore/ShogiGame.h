#ifndef SHOGI_SHOGIGAME_H
#define SHOGI_SHOGIGAME_H


#include "ShogiGameAPI.h"
#include "SaveAndLoad/GameSaver.h"
#include "SaveAndLoad/GameLoader.h"
#include "GameLogic/ShogiGameLogic.h"

class ShogiGame : public ShogiGameAPI
{

public:
    ShogiGame();
    virtual void initGame() override;
    virtual Player getCurrentPlayer() override;
    virtual void pickPiece(const Position &position) override;
    virtual void unPickPiece() override;
    virtual void movePiece(const Position &position) override;
    virtual void promotePiece(const Position &position) override;
    virtual void dropPiece(const PieceType pt, const Position &position) override;
    virtual AbstractBoard &getBoard() override;
    virtual ListOfGameSituations& getGameSituation() override;
    virtual ~ShogiGame();

private:
    AbstractBoard* board;
    AbstractShogiGameLogic* gameLogic;
    AbstractGameLoader* gameLoader;
    AbstractGameSaver* gameSaver;
    ListOfGameSituations gameSituations;
    Piece *pickedPiece = nullptr;
    Player currentPlayer = Sente;

    Player transformPlayer(Player player) const;
};


#endif //SHOGI_SHOGIGAME_H
