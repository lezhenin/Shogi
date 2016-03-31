
#include "ConsoleGame.h"

ConsoleGame::ConsoleGame()
{
    game = new Shogi();
}

void ConsoleGame::start()
{
    game->initGame();
    isRun = true;
    while(isRun)
    {

    }
}

void ConsoleGame::stop()
{
    isRun = false;
}

ConsoleGame::~ConsoleGame()
{
    delete game;
}







