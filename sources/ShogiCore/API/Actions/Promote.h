#ifndef SHOGI_PROMOTE_H
#define SHOGI_PROMOTE_H


#include "Action.h"
#include "../ShogiGameAPI.h"

class Promote : public Action
{
public:

    Promote(ShogiGameAPI *shogiGame, const Position &position) : shogiGame(shogiGame), position(position) { }

    void execute() override
    {
        try
        {
            memento = shogiGame->getBoard().getMemento();
            shogiGame->promotePiece(position);
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


    virtual ~Promote()
    {
        if(!memento)
        {
            delete memento;
        }
    }
private:
    ShogiGameAPI *shogiGame;
    Position position;
    AbstractBoardMemento *memento = nullptr ;

};


#endif //SHOGI_PROMOTE_H
