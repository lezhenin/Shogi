#include <iostream>
#include <algorithm>
#include <fstream>
#include "Game.h"
#include "MainMenu.h"
#include "../../ShogiCore/API/Shogi.h"
#include "../../ShogiCore/SaveAndLoad/JSON/JSONSaveManager.h"

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
    bool successful = false;
    while(!successful)
    {
        std::cin >> input;
        try
        {
            commandID = tableOfCommands.at(input);
            switch (commandID)
            {
                case 0:
                {
                    successful = pick();
                    break;
                }
                case 1:
                {
                    successful = unpick();
                    break;
                }
                case 2:
                {
                    successful = move();
                    break;
                }
                case 3:
                {
                    successful = drop();
                    break;
                }
                case 4:
                {
                    stop();
                    successful = true;
                    break;
                }
                case 5:
                {
                    printListOfCapturedPieces(Sente);
                    printListOfCapturedPieces(Gote);
                    successful = true;
                    break;
                }
                case 6:
                {
                    successful = undo();
                    break;
                }
                case 7:
                {
                    successful = redo();
                    break;
                }
                case 8:
                {
                    successful = save();
                    break;
                }
                case 9:
                {
                    successful = load();
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
    std::cout << "Sente - "         << board.getCapturedPieces(Sente).size() << std::endl;
    std::cout << "Gote - "          << board.getCapturedPieces(Gote).size()  << std::endl;
    std::cout << std::endl;
}

void Game::printListOfCapturedPieces(const Player &player) const
{
    ListOfPieces &pieces = game->getBoard().getCapturedPieces(player);

    std::cout << tableOfPlayers.at(player) << ":" << std::endl;

    std::cout << "Pawn - "           << countPieces(Pawn,          player, pieces) << std::endl;
    std::cout << "Lance - "          << countPieces(Lance,         player, pieces) << std::endl;
    std::cout << "Knight - "         << countPieces(Knight,        player, pieces) << std::endl;
    std::cout << "Bishop - "         << countPieces(Bishop,        player, pieces) << std::endl;
    std::cout << "Rook - "           << countPieces(Rook,          player, pieces) << std::endl;
    std::cout << "Silver General - " << countPieces(SilverGeneral, player, pieces) << std::endl;
    std::cout << "Gold General - "   << countPieces(GoldGeneral,   player, pieces) << std::endl;
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

bool Game::checkPosition(int horizontal, int vertical) const
{
    return (horizontal >= 1 && horizontal <= AbstractBoard::BOARD_HEIGHT &&
            vertical   >= 1 && vertical   <= AbstractBoard::BOARD_WIDTH );
}

bool Game::pick() const
{
    int horizontal, vertical;
    std::cin >> horizontal >> vertical;
    std::cin.clear();
    if (checkPosition(horizontal, vertical))
    {
        try
        {
            game->pickPiece(Position(horizontal, vertical));
            return true;
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    else
    {
        std::cout << "Bad arguments of command" << std::endl;
    }
    return false;
}

bool Game::unpick() const
{
    game->unPickPiece();
    return true;
}

bool Game::move() const
{
    int horizontal, vertical;
    std::cin >> horizontal >> vertical;
    std::cin.clear();
    if (checkPosition(horizontal, vertical))
    {
        try
        {
            game->movePiece(Position(horizontal, vertical));
            return true;
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    else
    {
        std::cout << "Bad arguments of command" << std::endl;
    }
    return false;
}

bool Game::drop() const
{
    int horizontal, vertical;
    std::string type;
    std::cin >> type >> horizontal >> vertical;
    std::cin.clear();
    try
    {
        PieceType pieceType;
        pieceType = tableOfTypes.at(type);
        if (checkPosition(horizontal, vertical))
        {
            try
            {
                game->dropPiece(pieceType, Position(horizontal, vertical));
                return true;
            }
            catch (std::exception &e)
            {
                std::cout << e.what() << std::endl;
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
    return false;
}

bool Game::undo() const
{
    if(!game->undo())
    {
        std::cout << "Can't undo move!" << std::endl;
    }
    return true;
}

bool Game::redo() const
{
    if(!game->redo())
    {
        std::cout << "Can't redo move!" << std::endl;
    }
    return true;
}

int Game::countPieces(const PieceType pieceType, const Player &player, const ListOfPieces &pieces) const
{
    Piece piece(pieceType,player);
    return std::count_if(pieces.begin(), pieces.end(), std::bind1st(std::mem_fun(&Piece::equals), &piece));
}

bool Game::save() const
{
    std::string fileName;

    std::cout << "Enter name of save file: " << std::endl;
    std::cin >> fileName;

    std::ofstream save(fileName);

    if(save.bad() || save.fail() || save.eof())
    {
        std::cout << "Can't open file." << std::endl;
        return false;
    }

    JSONSaveManager *saveManager = new JSONSaveManager();
    game->save(saveManager);

    save << saveManager->getJSONString();
    save.close();

    std::cout << "Saved!" << std::endl;

    delete saveManager;
    return true;
}

bool Game::load() const
{
    std::string fileName;

    std::cout << "Enter name of save file: " << std::endl;
    std::cin >> fileName;

    std::ifstream save(fileName);

    if(save.bad() || save.fail() || save.eof())
    {
        std::cout << "Can't open file." << std::endl;
        return false;
    }

    std::string JSONSaveString;
    while(!save.eof())
    {
        JSONSaveString.push_back((char)save.get());
    }
    JSONSaveString.pop_back();
    JSONSaveManager *saveManager = new JSONSaveManager(JSONSaveString);
    game->load(saveManager);

    save.close();

    std::cout << "Loaded!" << std::endl;

    delete saveManager;
    return true;
}


























