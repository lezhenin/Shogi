#ifndef SHOGI_UNPICK_H
#define SHOGI_UNPICK_H


#include "Command.h"

class UnPick : public Command
{

public:
    UnPick(ShogiGameAPI *game) : game(game) { }
    virtual void execute() override
    {
        try
        {
            game->unPickPiece();
        }
        catch(std::exception &e)
        {
            throw &e;
        }
    }


private:
    ShogiGameAPI *game;
};



#endif //SHOGI_UNPICK_H
