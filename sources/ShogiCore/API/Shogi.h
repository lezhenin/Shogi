#ifndef SHOGI_SHOGI_H
#define SHOGI_SHOGI_H

#include <stack>
#include "../GameLogic/GameSituations/PromotionIsAvailable.h"
#include "../GameLogic/GameSituations/Shah.h"
#include "../GameLogic/GameSituations/Mate.h"
#include "ShogiAPI.h"
#include "../GameLogic/ShogiGameLogic.h"
#include "../SaveAndLoad/GameLoader.h"
#include "../SaveAndLoad/GameSaver.h"
#include "Actions/Action.h"

class Shogi: public ShogiAPI
{

public:

    Shogi();
    virtual void initGame() override;
    virtual Player getCurrentPlayer() override;
    virtual void movePiece(const Position &from, const Position &to) override;
    virtual void promotePiece(const Position &position) override;
    virtual void dropPiece(const PieceType pt, const Position &position) override;
    virtual AbstractBoard &getBoard() override;
    virtual ListOfGameSituations& getGameSituation() override;
    virtual ~Shogi();

    virtual void undo() override;

private:

    ShogiGameAPI *shogiGame;
    std::stack<Action*> done;


};


#endif //SHOGI_SHOGI_H
