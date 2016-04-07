#include <sstream>
#include <iostream>
#include <algorithm>
#include "ConsoleGame.h"
#include "Commands/Pick.h"
#include "Commands/UnPick.h"
#include "Commands/Move.h"
#include "Commands/Drop.h"
#include "Commands/Exit.h"
#include "Commands/ShowCapturedPieces.h"

ConsoleGame::ConsoleGame()
{
    game = new Shogi();
}

void ConsoleGame::start()
{
    std::cout << "Start new game" << std::endl;
    game->initGame();
    print();
    isRun = true;
    while(isRun)
    {
        Command *command = inputCommand();
        if (command != nullptr)
            try
            {
                command->execute();
            }
            catch(std::exception &e)
            {
                std::cout << "Game error" << std::endl;
            }
        print();
        delete command;
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
       tmp = tableOfCommands.at(str);
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
            std::cin.clear();
            if (h>=1 && h<=9 && v>=1 && v<=9)
            {
                Command *ptr = new Pick(game,h,v);
                std::cout << "Picked piece: " << h << " " << v << std::endl;
                return ptr;
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
            std::cin.clear();
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
            std::string type;
            std::cin >> type >> h >> v;
            std::cin.clear();
            PieceType pieceType;
            try
            {
                pieceType = tableOfTypes.at(type);
            }
            catch (std::exception &e)
            {
                std::cout << "Bad arguments of command" << std::endl;
                return nullptr;
            }
            if (h>=1 && h<=9 && v>=1 && v<=9)
            {
                return new Drop(game, pieceType, h,v);
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
        case 5:
        {
            return new ShowCapturedPieces(this);
        }
        default:
        {
            return nullptr;
        }
    }
}

void ConsoleGame::printBoard(AbstractBoard &board)
{
    for(int j=9; j>=1; j--)
    {
        std::cout << " " << j << "  ";
    }
    std::cout << std::endl;
    for(int i=1; i<=9; i++)
    {
        for(int j=9; j>=1; j--)
        {
            Piece *p = board.getPiece(Position(i,j));

            if (p == nullptr)
            {
                std::cout <<  "*** ";
            }
            else
            {
                std:: cout << ((p->getPlayer()==Sente) ? "s" : "g") << tableOfLabels.at(p->getType()) << " ";
            }
        }
        std::cout << " " << i << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Captured pieces:" << std::endl;
    std::cout << "Sente - " << board.getCapturedPieces(Sente).size() << std::endl;
    std::cout << "Gote - " << board.getCapturedPieces(Gote).size() << std::endl;
    std::cout << std::endl;
}
//todo refactor
void ConsoleGame::printListOfCapturedPieces(Player player)
{
    ListOfPieces &pieces = game->getBoard().getCapturedPieces(player);
    Piece tmp(Pawn,player);
    std::cout << tableOfPlayers.at(player) << ":" << std::endl;
    std::cout << "Pawn - "<< std::count_if(pieces.begin(),pieces.end(),std::bind1st(std::mem_fun(&Piece::equals),&tmp)) << std::endl;
    tmp = Piece(Lance, player);
    std::cout << "Lance - "<< std::count_if(pieces.begin(),pieces.end(),std::bind1st(std::mem_fun(&Piece::equals),&tmp)) << std::endl;
    tmp = Piece(Knight, player);
    std::cout << "Knight - "<< std::count_if(pieces.begin(),pieces.end(),std::bind1st(std::mem_fun(&Piece::equals),&tmp)) << std::endl;
    tmp = Piece(Bishop, player);
    std::cout << "Bishop - "<< std::count_if(pieces.begin(),pieces.end(),std::bind1st(std::mem_fun(&Piece::equals),&tmp)) << std::endl;
    tmp = Piece(Rook, player);
    std::cout << "Rook - "<< std::count_if(pieces.begin(),pieces.end(),std::bind1st(std::mem_fun(&Piece::equals),&tmp)) << std::endl;
    tmp = Piece(SilverGeneral, player);
    std::cout << "Silver General - " << std::count_if(pieces.begin(),pieces.end(),std::bind1st(std::mem_fun(&Piece::equals),&tmp)) << std::endl;
    tmp = Piece(GoldGeneral,player);
    std::cout << "Gold General - " << std::count_if(pieces.begin(),pieces.end(),std::bind1st(std::mem_fun(&Piece::equals),&tmp)) << std::endl;
}

void ConsoleGame::printMessages(ListOfGameSituations &list)
{
    while (!list.empty())
    {
        GameSituation* gameSituation = game->getGameSituation().front().get();
        std:: cout << gameSituation->getMessage() << std::endl;
        if (gameSituation->isEndOfGame())
        {
            stop();
        }
        if(gameSituation->isExecutable())
        {
            std::cout << "Do you want to do it?(yes/no)" << std::endl;
            std::string answer="";
            std::cin >> answer;
            while(answer!="yes" && answer!="no")
            {
                std::cout << "Unknown command" << std::endl;
                std::cin >> answer;
            }
            if(answer=="yes")
            {
                gameSituation->execute();
                std::cout << "Player: " << tableOfPlayers.at(game->getCurrentPlayer()) << std::endl;
                printBoard(game->getBoard());
            }
        }
        list.pop();
    }

}

void ConsoleGame::print()
{
    std::cout << "Player: " << tableOfPlayers.at(game->getCurrentPlayer()) << std::endl;
    printBoard(game->getBoard());
    printMessages(game->getGameSituation());
}

















