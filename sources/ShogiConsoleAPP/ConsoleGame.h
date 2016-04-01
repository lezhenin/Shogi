#ifndef SHOGI_GAME_H
#define SHOGI_GAME_H


#include "../ShogiCore/Shogi.h"
#include "Commands/Command.h"

class ConsoleGame
{
public:

    ConsoleGame();
    void start();
    void stop();
    virtual ~ConsoleGame();

private:
    Command *inputCommand();
    void printBoard(AbstractBoard *board);

    ShogiGameAPI *game;
    bool isRun = false;
    std::map<std::string,int> commands = {{"pick",0},{"unpick",1},{"move",2},{"drop",3},{"exit",4}};
};


#endif //SHOGI_GAME_H