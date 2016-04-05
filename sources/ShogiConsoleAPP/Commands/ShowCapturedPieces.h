#ifndef SHOGI_SHOWCAPTUREDPIECES_H
#define SHOGI_SHOWCAPTUREDPIECES_H

#include "Command.h"

class ShowCapturedPieces : public Command
{
public:
    explicit ShowCapturedPieces(ConsoleGame *game) : game(game) { }
    virtual void execute() override
    {
            game->printListOfCapturedPieces(Sente);
            game->printListOfCapturedPieces(Gote);
    }

private:
    ConsoleGame *game;
};


#endif //SHOGI_SHOWCAPTUREDPIECES_H
