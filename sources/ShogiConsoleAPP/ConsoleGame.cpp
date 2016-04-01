#include <sstream>
#include <iostream>
#include "ConsoleGame.h"
#include "Commands/Pick.h"
#include "Commands/UnPick.h"
#include "Commands/Move.h"
#include "Commands/Drop.h"
#include "Commands/Exit.h"

ConsoleGame::ConsoleGame()
{
    game = new Shogi();
}

void ConsoleGame::start()
{
    std::cout << "Start new game" << std::endl;
    game->initGame();
    printBoard(&game->getBoard());
    isRun = true;
    while(isRun)
    {
        Command *command = inputCommand();
        try
        {
            command->execute();
        }
        catch(std::exception &e)
        {
            std::cout << "Game error" << std::endl;
        }
        printBoard(&game->getBoard());
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

Command *ConsoleGame::inputCommand()
{
    std::string str;
    std::cin >> str;
    int tmp;
    try
    {
       tmp = commands.at(str);
    }
    catch (std::exception &e)
    {
        std::cout << "Unknown command" << std::endl;
        return nullptr;
    }
    switch (tmp)
    {
        case 0:
        {
            int h, v;
            std::cin >> h >> v;
            if (h>=1 && h<=9 && v>=1 && v<=9)
            {
                return new Pick(game,h,v);
            }
            else
            {
                std::cout << "Bad arguments of command" << std::endl;
                return nullptr;
            }
        }
        case 1:
        {
            return new UnPick(game);
        }
        case 2:
        {
            int h, v;
            std::cin >> h >> v;
            if (h>=1 && h<=9 && v>=1 && v<=9)
            {
                return new Move(game,h,v);
            }
            else
            {
                std::cout << "Bad arguments of command" << std::endl;
                return nullptr;
            }
        }
        case 3:
        {
            int h, v;
            std::cin >> h >> v;
            if (h>=1 && h<=9 && v>=1 && v<=9)
            {
                return new Drop(game,h,v);
            }
            else
            {
                std::cout << "Bad arguments of command" << std::endl;
                return nullptr;
            }
        }
        case 4:
        {
            return new Exit(this);
        }
        default:
        {
            return nullptr;
        }
    }
}

void ConsoleGame::printBoard(AbstractBoard *board)
{
    for(int i=1; i<=9; i++)
    {
        for(int j=9; j>=1; j--)
        {
            Piece *p = board->getPiece(Position(i,j));

            if (p==0) std::cout <<  "* ";
            else std:: cout << "0 ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}











