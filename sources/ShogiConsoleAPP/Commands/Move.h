#ifndef SHOGI_MOVE_H
#define SHOGI_MOVE_H
#include "Command.h"


class Move : public Command
{
public:
    Move(ShogiAPI *game, int h1, int v1, int h2, int v2) : game(game), from(h1,v1), to(v2,h2)  { }
    virtual void execute() override
    {
        try
        {
            game->movePiece(to, from);
        }
        catch(std::exception &e)
        {
            throw e;
        }
    }

private:
    ShogiAPI *game;
    Position from;
    Position to;

};


#endif //SHOGI_MOVE_H
