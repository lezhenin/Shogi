#ifndef SHOGI_EXIT_H
#define SHOGI_EXIT_H


#include "Command.h"

class Exit : public Command
{

public:
    Exit(ConsoleGame *consoleGame) : consoleGame(consoleGame) { }
    virtual void execute() override
    {
        consoleGame->stop();
    }


private:
    ConsoleGame *consoleGame;
};


#endif //SHOGI_EXIT_H
