#ifndef SHOGI_MOVE_H
#define SHOGI_MOVE_H


#include "Action.h"
#include "../../Model/Position.h"
#include "../ShogiGameAPI.h"

class Move : public Action
{

public:


    Move(ShogiGameAPI *shogiGame, const Position &from, const Position &to) : shogiGame(shogiGame), from(from), to(to) { }

    virtual void execute() override
    {
        try
        {
            shogiGame->pickPiece(from);
            shogiGame->movePiece(to);
        }
        catch (std::exception &e)
        {
            throw e;
        }
    }

    virtual void unExecute() override
    {
        shogiGame->getBoard().setMemento(memento);
        delete memento;
        memento = nullptr;
    }


    virtual ~Move()
    {
        if(!memento)
        {
            delete memento;
        }
    }

private:
    ShogiGameAPI *shogiGame;
    Position from;
    Position to;
    AbstractBoardMemento *memento = nullptr;

};


#endif //SHOGI_MOVE_H
