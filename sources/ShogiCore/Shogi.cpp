#include <algorithm>
#include "Shogi.h"
#include "ShogiGame.h"
#include "Actions/Move.h"
#include "Actions/Drop.h"
#include "Actions/Promote.h"


Shogi::Shogi()
{
    shogiGame = new ShogiGame();
}

void Shogi::initGame()
{
    shogiGame->initGame();
}

Player Shogi::getCurrentPlayer()
{
    return shogiGame->getCurrentPlayer();
}

Shogi::~Shogi()
{
    delete shogiGame;
    while(!done.empty())
    {
        delete done.top();
        done.pop();
    }
}

ListOfGameSituations &Shogi::getGameSituation()
{
    return shogiGame->getGameSituation();
}

AbstractBoard &Shogi::getBoard()
{
    return shogiGame->getBoard();
}

void Shogi::movePiece(const Position &from, const Position &to)
{
    Action* action = new Move(shogiGame,from,to);
    action->execute();
    done.push(action);
}

void Shogi::dropPiece(const PieceType pt, const Position &position)
{
    Action* action = new Drop(shogiGame,pt,position);
    action->execute();
    done.push(action);
}

void Shogi::promotePiece(const Position &position)
{
    Action* action = new Promote(shogiGame,position);
    action->execute();
    done.push(action);
}

void Shogi::undo()
{
    done.top()->unExecute();
    delete done.top();
    done.pop();
}



















































