#ifndef SHOGI_MOVE_H
#define SHOGI_MOVE_H
#include "Command.h"


class Move : public Command
{

public:
    Move(ShogiGameAPI *game, int h, int v) : game(game), position(h,v) { }
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


#endif //SHOGI_MOVE_H
