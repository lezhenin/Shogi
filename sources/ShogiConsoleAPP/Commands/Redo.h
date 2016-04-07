#ifndef SHOGI_REDO_H
#define SHOGI_REDO_H


#include "Command.h"

class Redo : public Command
{
public:
    Redo(ShogiGameAPI *game) : game(game) { }
    virtual void execute() override
    {
        try
        {
            game->redo();
        }
        catch(std::exception &e)
        {
            throw e;
        }
    }

private:
    ShogiGameAPI *game;
};



#endif //SHOGI_REDO_H
