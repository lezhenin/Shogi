#ifndef SHOGI_DROP_H
#define SHOGI_DROP_H

#include "Action.h"
#include "../ShogiGameAPI.h"

class Drop : public Action
{
public:

    Drop(ShogiGameAPI *shogiGame, PieceType pieceType, const Position &position) : shogiGame(shogiGame),
                                                                                   pieceType(pieceType),
                                                                                   position(position) { }

    void execute() override
    {
        try
        {
            shogiGame->dropPiece(pieceType, position);
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


    virtual ~Drop()
    {
        if(!memento)
        {
            delete memento;
        }
    }

private:
    ShogiGameAPI *shogiGame;
    PieceType pieceType;
    Position position;
    AbstractBoardMemento *memento = nullptr;
};


#endif //SHOGI_DROP_H
