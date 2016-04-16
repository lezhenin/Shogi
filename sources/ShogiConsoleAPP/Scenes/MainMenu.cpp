#include <iostream>
#include "MainMenu.h"
#include "Game.h"
#include "Help.h"

void MainMenu::show()
{
    std::cout << "1. Start new game" << std::endl
              << "2. Load game" << std::endl
              << "3. Help" << std::endl
              << "4. Exit" << std::endl;

    std::string input;
    int choice;
    bool error = true;
    while(error)
    {
        std::cin >> input;
        try
        {
            choice = std::stoi(input);
        }
        catch (std::exception &e)
        {
            choice = 0;
        }
        error = false;
        switch (choice) {
            case 1:
            {
                next = new Game(true);
                break;
            }
            case 2:
            {
                next = new Game(false);
                break;
            }
            case 3:
            {
                next = new Help();
                break;
            }
            case 4:
            {
                next = nullptr;
                break;
            }
            default:
            {
                error = true;
                std::cout << "Unknown command" << std::endl;
            }
        }
    }

}

