

#ifndef SHOGI_PICK_H
#define SHOGI_PICK_H


#include "Command.h"

class Pick : public Command
{

public:
    Pick(ShogiGameAPI *game, int h, int v) : game(game), position(h,v) { }
    virtual void execute() override
    {
        try
        {
            game->pickPiece(position);
        }
        catch(std::exception &e)
        {
            throw e;
        }
    }


private:
    ShogiGameAPI *game;
    Position position;
};



#endif //SHOGI_PICK_H
