#include <iostream>
#include <algorithm>
#include "Game.h"
#include "MainMenu.h"
#include "../../ShogiCore/Shogi.h"

void Game::show()
{
    std::cout << "Start new game" << std::endl;
    game->initGame();
    print();
    isRun = true;
    while(isRun)
    {
        input();
        print();
    }
}

void Game::input()
{

    std::string input;
    int commandID;
    bool listenUser = true;
    while(listenUser)
    {
        std::cin >> input;
        try
        {
            commandID = tableOfCommands.at(input);
            switch (commandID)
            {
                case 0:
                {
                            //TODO: выделить метод
                //TODO: переименовать h и v
                    int horizontal, vertical;
                    std::cin >> horizontal >> vertical;
                    std::cin.clear();
                    if (horizontal >= 1 && horizontal <= AbstractBoard::BOARD_HEIGHT && vertical >= 1 && vertical <= AbstractBoard::BOARD_WIDTH)
                    {
                        try
                        {
                            game->pickPiece(Position(horizontal, vertical));
                            listenUser = false;
                        }
                        catch (std::exception &e)
                        {
                            std::cout << "Game error" << std::endl;
                        }
                    }
                    else
                    {
                        std::cout << "Bad arguments of command" << std::endl;
                    }
                    break;
                }
                case 1:
                {
                    game->unPickPiece();
                    listenUser = false;
                    break;
                }
                case 2:
                {
                            //TODO: выделить метод
                //TODO: переименовать h и v
                    int h, v;
                    std::cin >> h >> v;
                    std::cin.clear();
                    if (h >= 1 && h <= 9 && v >= 1 && v <= 9)
                    {
                        try
                        {
                            game->movePiece(Position(h, v));
                            listenUser = false;
                        }
                        catch (std::exception &e)
                        {
                            std::cout << "Game error" << std::endl;
                        }
                    }
                    else
                    {
                        std::cout << "Bad arguments of command" << std::endl;
                    }
                    break;
                }
                case 3:
                {
                            //TODO: выделить метод
                //TODO: переименовать h и v
                    int h, v;
                    std::string type;
                    std::cin >> type >> h >> v;
                    std::cin.clear();
                    try
                    {
                        PieceType pieceType;
                        pieceType = tableOfTypes.at(type);
                        if (h >= 1 && h <= 9 && v >= 1 && v <= 9)
                        {
                            try
                            {
                                game->dropPiece(pieceType, Position(h, v));
                                listenUser = false;
                            }
                            catch (std::exception &e)
                            {
                                std::cout << "Game error" << std::endl;
                            }
                        }
                        else
                        {
                            std::cout << "Bad arguments of command" << std::endl;
                        }
                    }
                    catch (std::exception &e) {
                        std::cout << "Bad arguments of command" << std::endl;
                    }
                    break;
                }
                case 4:
                {
                    stop();
                    listenUser = false;
                    break;
                }
                case 5:
                {
                    printListOfCapturedPieces(Sente);
                    printListOfCapturedPieces(Gote);
                    listenUser = false;
                    break;
                }
                case 6:
                {
                    game->undo();
                    listenUser = false;
                    break;
                }
                case 7:
                {
                    game->redo();
                    listenUser = false;
                    break;
                }
                default:
                {

                }
            }

        }
        catch (std::exception &e)
        {
            std::cout << "Unknown command" << std::endl;
        }
    }


}

void Game::printBoard(AbstractBoard &board) const
{
    for(int j = AbstractBoard::BOARD_WIDTH; j >= 1; j--)
    {
        std::cout << " " << j << "  ";
    }
    std::cout << std::endl;
    for(int i = 1; i <= AbstractBoard::BOARD_HEIGHT; i++)
    {
        for(int j = AbstractBoard::BOARD_WIDTH; j >= 1; j--)
        {
            Piece *p = board.getPiece(Position(i, j));
            if (p == nullptr)
            {
                std::cout <<  "*** ";
            }
            else
            {
                std:: cout << ((p->getPlayer() == Sente) ? "s" : "g") << tableOfLabels.at(p->getType()) << " ";
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
void Game::printListOfCapturedPieces(Player player) const
{
    ListOfPieces &pieces = game->getBoard().getCapturedPieces(player);
    Piece tmp(Pawn, player);
    std::cout << tableOfPlayers.at(player) << ":" << std::endl;
    std::cout << "Pawn - "<< std::count_if(pieces.begin(), pieces.end(), std::bind1st(std::mem_fun(&Piece::equals), &tmp)) << std::endl;
    tmp = Piece(Lance, player); 
    std::cout << "Lance - "<< std::count_if(pieces.begin(), pieces.end(), std::bind1st(std::mem_fun(&Piece::equals), &tmp)) << std::endl;
    tmp = Piece(Knight, player);
    std::cout << "Knight - "<< std::count_if(pieces.begin(), pieces.end(), std::bind1st(std::mem_fun(&Piece::equals), &tmp)) << std::endl;
    tmp = Piece(Bishop, player);
    std::cout << "Bishop - "<< std::count_if(pieces.begin(), pieces.end(), std::bind1st(std::mem_fun(&Piece::equals), &tmp)) << std::endl;
    tmp = Piece(Rook, player);
    std::cout << "Rook - "<< std::count_if(pieces.begin(), pieces.end(), std::bind1st(std::mem_fun(&Piece::equals), &tmp)) << std::endl;
    tmp = Piece(SilverGeneral, player);
    std::cout << "Silver General - " << std::count_if(pieces.begin(), pieces.end(), std::bind1st(std::mem_fun(&Piece::equals), &tmp)) << std::endl;
    tmp = Piece(GoldGeneral, player);
    std::cout << "Gold General - " << std::count_if(pieces.begin(), pieces.end(), std::bind1st(std::mem_fun(&Piece::equals), &tmp)) << std::endl;
}

void Game::printMessages(ListOfGameSituations &list)
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
            std::string answer = "";
            std::cin >> answer;
            while(answer != "yes" && answer != "no")
            {
                std::cout << "Unknown command" << std::endl;
                std::cin >> answer;
            }
            if(answer == "yes")
            {
                gameSituation->execute();
                std::cout << "Player: " << tableOfPlayers.at(game->getCurrentPlayer()) << std::endl;
                printBoard(game->getBoard());
            }
        }
        list.pop();
    }

}

void Game::print()
{
    std::cout << "Player: " << tableOfPlayers.at(game->getCurrentPlayer()) << std::endl;
    printBoard(game->getBoard());
    printMessages(game->getGameSituation());
}

void Game::stop()
{
    isRun = false;
    next = new MainMenu();
}

Game::~Game()
{
    delete game;
}

Game::Game()
{
    game = new Shogi();
}



