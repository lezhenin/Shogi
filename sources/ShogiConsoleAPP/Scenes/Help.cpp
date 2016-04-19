#include <iostream>
#include "Help.h"
#include "MainMenu.h"

void Help::show()
{
    std::cout << "Designation of pieces:" << std::endl
              << "First symbol  - player: s - \"sente\" or g - \"gote\"." << std::endl
              << "Second symbol - promotion: n - \"not promoted\" or p - \"promoted\"" << std::endl
              << "Third symbol  - type of piece." << std::endl << std::endl

              << "Table of piece:" << std::endl
              << "king           - \"K\"" << std::endl
              << "gold General   - \"G\"" << std::endl
              << "rook           - \"R\"" << std::endl
              << "bishop         - \"B\"" << std::endl
              << "silver General - \"S\"" << std::endl
              << "knight         - \"H\"" << std::endl
              << "lance          - \"L\"" << std::endl
              << "pawn           - \"P\"" << std::endl  << std::endl

              << "List of commands:" << std::endl
              << "pick <horizontal> <vertical>,"                                          << std::endl
              << "p <horizontal> <vertical>              - pick piece"                    << std::endl
              << "unpick, up                             - unpick piece"                  << std::endl
              << "move <horizontal> <vertical>,"                                          << std::endl
              << "m <horizontal> <vertical>              - move picked piece"             << std::endl
              << "drop <type> <horizontal> <vertical>,"                                   << std::endl
              << "d <type> <horizontal> <vertical>       - drop captured piece"           << std::endl
              << "undo, u                                - undo last movie"               << std::endl
              << "redo, r                                - redo last movie"               << std::endl
              << "show, sh                            	 - show list of captured pieces"  << std::endl
              << "save, s                              	 - save game"                     << std::endl
              << "load, l                              	 - load game"                     << std::endl
              << "exit, e                              	 - return to main menu"           << std::endl << std::endl

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

