#include <iostream>
#include "MainMenu.h"
#include "Game.h"
#include "Help.h"

void MainMenu::show()
{
    std::cout << "1. Start new game" << std::endl
              << "2. Load game" << std::endl
              << "3. Settings" << std::endl
              << "4. Help" << std::endl
              << "5. Exit" << std::endl;
    int choice;
    std::cin >> choice;
    bool x = true;
    while(x)
    {
        x = false;
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
            case 4:
            {
                next = new Help();
                break;
            }
            case 5:
            {
                next = nullptr;
                break;
            }
            default:
            {
                x = true;
                std::cout << "Unknown command";
            }
        }
    }

}

