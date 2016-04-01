#ifndef SHOGI_DROP_H
#define SHOGI_DROP_H


#include "Command.h"

class Drop : public Command
{

public:
    Drop(ShogiGameAPI *game, int h, int v) : game(game), position(h,v) { }
    virtual void execute() override
    {
        try
        {
            game->movePiece(position);
        }
        catch(std::exception &e)
        {
            throw &e;
        }
    }


private:
    ShogiGameAPI *game;
    Position position;
};


#endif //SHOGI_DROP_H
