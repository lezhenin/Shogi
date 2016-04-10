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

    std::string str;
    int tmp;
    bool x = true;
    while(x)
    {
        std::cin >> str;
        try
        {
            tmp = tableOfCommands.at(str);
            switch (tmp)
            {
                case 0:
                {
                    int h, v;
                    std::cin >> h >> v;
                    std::cin.clear();
                    if (h >= 1 && h <= 9 && v >= 1 && v <= 9)
                    {
                        try
                        {
                            game->pickPiece(Position(h, v));
                            x = false;
                        }
                        catch (std::exception) /// (std::exception &e)
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
                    x = false;
                    break;
                }
                case 2:
                {
                    int h, v;
                    std::cin >> h >> v;
                    std::cin.clear();
                    if (h >= 1 && h <= 9 && v >= 1 && v <= 9)
                    {
                        try
                        {
                            game->movePiece(Position(h, v));
                            x = false;
                        }
                        catch (std::exception) /// (std::exception &e)
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
                                x = false;
                            }
                            catch (std::exception) /// (std::exception &e)
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
                    x = false;
                    break;
                }
                case 5:
                {
                    printListOfCapturedPieces(Sente);
                    printListOfCapturedPieces(Gote);
                    x = false;
                    break;
                }
                case 6:
                {
                    game->undo();
                    x = false;
                    break;
                }
                case 7:
                {
                    game->redo();
                    x = false;
                    break;
                }
                default:
                {

                }
            }

        }
        catch (std::exception &e) {
            std::cout << "Unknown command" << std::endl;
        }
    }


}

void Game::printBoard(AbstractBoard &board)
{
    for(int j=9; j>=1; j--) /// for (int j = 9; j >= 1; j--) 
    {
        std::cout << " " << j << "  ";
    }
    std::cout << std::endl;
    for(int i=1; i<=9; i++) /// и тут тоже напиши красиво
    {
        for(int j=9; j>=1; j--) /// ....
        {
            Piece *p = board.getPiece(Position(i,j)); /// Position(i, j)

            if (p == nullptr)
            {
                std::cout <<  "*** ";
            }
            else
            {
                std:: cout << ((p->getPlayer()==Sente) ? "s" : "g") << tableOfLabels.at(p->getType()) << " "; /// почему ты отделяешь 
                /// операции присваивания пробелами (строка 192, например), а логические операции нет
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
void Game::printListOfCapturedPieces(Player player)
{
    ListOfPieces &pieces = game->getBoard().getCapturedPieces(player);
    Piece tmp(Pawn,player);
    std::cout << tableOfPlayers.at(player) << ":" << std::endl;
    /// поставь пробелы после запятых - легче читать будет, в Game::input хорошо же было
    std::cout << "Pawn - "<< std::count_if(pieces.begin(), pieces.end(), std::bind1st(std::mem_fun(&Piece::equals), &tmp)) << std::endl;
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
            std::string answer=""; /// а тут не отделил присваивание
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



