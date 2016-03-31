
#ifndef SHOGI_GAME_H
#define SHOGI_GAME_H


#include "../ShogiCore/Shogi.h"

class ConsoleGame
{
public:

    ConsoleGame();
    void start();
    void stop();
    virtual ~ConsoleGame();

private:

    void printBoard();
    ShogiGameAPI *game;
    bool isRun = false;
};


#endif //SHOGI_GAME_H
