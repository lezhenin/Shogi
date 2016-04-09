#include <iostream>
#include "Help.h"
#include "MainMenu.h"

void Help::show()
{
    std::cout << "There will be help..." << std::endl
              << "Enter \"back\" to return back..." << std::endl;
    std::string command = "";
    while(command != "back")
    {
        std::cin >> command;
        if(command == "back")
        {
         next = new MainMenu();
        }
        else
        {
            std::cout << "Unknown command" << std::endl;
        }
    }

}

