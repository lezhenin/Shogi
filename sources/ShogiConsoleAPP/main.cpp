#include <iostream>
#include "ConsoleGame.h"

int main()
{
    try
    {
        ConsoleGame game;
        game.start();
    }
    catch(std::exception &e)
    {
        std::cout << e.what();
    }
    return 0;
}