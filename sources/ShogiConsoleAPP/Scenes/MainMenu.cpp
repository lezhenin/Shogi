#include <iostream>
#include "MainMenu.h"
#include "Game.h"
#include "Help.h"

void MainMenu::show()
{
    std::cout << "1. Start new game" << std::endl
              << "2. Load game" << std::endl
              << "3. Help" << std::endl
              << "0. Exit" << std::endl;

    int choice;
    bool error = true;
    while(error)
    {
        std::cin >> choice;
        error = false;
        switch (choice) {
            case 1:
            {
                next = new Game();
                break;
            }
            case 2:
            {
                next = new Game();
                break;
            }
            case 3:
            {
                next = new Help();
                break;
            }
            case 0:
            {
                next = nullptr;
                break;
            }
            default:
            {
                error = true;
                std::cout << "Unknown command";
            }
        }
    }

}

