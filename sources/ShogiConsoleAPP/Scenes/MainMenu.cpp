#include <iostream>
#include "MainMenu.h"
#include "Game.h"

void MainMenu::show()
{
    std::cout << "1. Start new game" << std::endl
              << "2. Load game" << std::endl
              << "3. Settings" << std::endl
              << "4. Help" << std::endl
              << "5. Exit" << std::endl;
    int choice;
    std::cin >> choice;
    switch (choice)
    {
        case 1:
        {
            next = new Game();
            break;
        }
        case 5:
        {
            next = nullptr;
            break;
        }
        default:
        {
            std::cout << "Unknown command";
        }
    }

}

