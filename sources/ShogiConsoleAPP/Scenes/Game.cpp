#include <iostream>
#include <algorithm>
#include <fstream>
#include "Game.h"
#include "MainMenu.h"
#include "../../ShogiCore/API/Shogi.h"
#include "../../ShogiCore/SaveAndLoad/JSON/JSONSaveManager.h"
#include "../../ShogiCore/Model/Exceptions/BadPositionException.h"

void Game::show()
{
    std::cout << "Start new game" << std::endl;
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
    std::cout << "Enter command:" << std::endl;
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
                    printListOfCapturedPieces(shogi::Sente);
                    printListOfCapturedPieces(shogi::Gote);
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
        std::getline(std::cin, input);
    }
}

void Game::printBoard(shogi::AbstractBoard &board) const
{
    bool isPicked = false;

    std::cout << " ";
    for(int j = shogi::AbstractBoard::BOARD_WIDTH; j >= 1; j--)
    {
        std::cout << " " << j << "  ";
    }
    std::cout << std::endl;

    //todo убрать все костыли когда-нибудь
    for(int i = 1; i <= shogi::AbstractBoard::BOARD_HEIGHT; i++)
    {
        for(int j = shogi::AbstractBoard::BOARD_WIDTH; j >= 1; j--)
        {
            shogi::Piece *samplePiece = board.getPiece(shogi::Position(i, j));
            try
            {
                isPicked = (samplePiece                             == game->getPickedPiece() ||
                            board.getPiece(shogi::Position(i,j+1))  == game->getPickedPiece()) &&
                           game->getPickedPiece() != nullptr;
            }
            catch (shogi::BadPositionException &e)
            {
                isPicked = samplePiece == game->getPickedPiece() &&
                           game->getPickedPiece() != nullptr;
            }
            std::cout << ((isPicked) ? "|" : " ");
            if (samplePiece == nullptr)
            {
                std::cout <<  "***";
            }
            else
            {
                std:: cout << ((samplePiece->getPlayer() == shogi::Sente) ? "s" : "g")
                           << tableOfLabels.at(samplePiece->getType());
            }
        }
        isPicked = (board.getPiece(shogi::Position(i,1)) == game->getPickedPiece() &&
                              game->getPickedPiece() != nullptr);
        std::cout << ((isPicked) ? "|" : " ") << i << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Captured pieces:" << std::endl;
    std::cout << "Sente - "         << board.getCapturedPieces(shogi::Sente).size() << std::endl;
    std::cout << "Gote - "          << board.getCapturedPieces(shogi::Gote).size()  << std::endl;
    std::cout << std::endl;
}

void Game::printListOfCapturedPieces(const shogi::Player &player) const
{
    shogi::ListOfPieces &pieces = game->getBoard().getCapturedPieces(player);

    std::cout << tableOfPlayers.at(player) << ":" << std::endl;

    std::cout << "Pawn - "           << countPieces(shogi::Pawn,          player, pieces) << std::endl;
    std::cout << "Lance - "          << countPieces(shogi::Lance,         player, pieces) << std::endl;
    std::cout << "Knight - "         << countPieces(shogi::Knight,        player, pieces) << std::endl;
    std::cout << "Bishop - "         << countPieces(shogi::Bishop,        player, pieces) << std::endl;
    std::cout << "Rook - "           << countPieces(shogi::Rook,          player, pieces) << std::endl;
    std::cout << "Silver General - " << countPieces(shogi::SilverGeneral, player, pieces) << std::endl;
    std::cout << "Gold General - "   << countPieces(shogi::GoldGeneral,   player, pieces) << std::endl;
}

void Game::printMessages(shogi::ListOfGameSituations &list)
{
    while (!list.empty())
    {
        shogi::GameSituation* gameSituation = game->getGameSituation().front().get();
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

Game::Game(bool newGame)
{
    game = new shogi::Shogi();

    if(newGame || !load());
    {
        game->load();
    }
}


bool Game::checkPosition(int horizontal, int vertical) const
{
    return (horizontal >= 1 && horizontal <= shogi::AbstractBoard::BOARD_HEIGHT &&
            vertical   >= 1 && vertical   <= shogi::AbstractBoard::BOARD_WIDTH );
}

bool Game::pick() const
{
    int horizontal = 0;
    int vertical = 0;
    std::cin >> horizontal >> vertical;
    std::cin.clear();
    if (checkPosition(horizontal, vertical))
    {
        try
        {
            game->pickPiece(shogi::Position(horizontal, vertical));
            std::cout << "Piece on square " << horizontal << " "
                      << vertical << " is picked." << std::endl;

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
    int horizontal = 0;
    int vertical = 0;
    std::cin >> horizontal >> vertical;
    std::cin.clear();
    if (checkPosition(horizontal, vertical))
    {
        try
        {
            game->movePiece(shogi::Position(horizontal, vertical));
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
    int horizontal = 0;
    int vertical = 0;
    std::string type;
    std::cin >> type >> horizontal >> vertical;
    std::cin.clear();
    try
    {
        shogi::PieceType pieceType;
        pieceType = tableOfTypes.at(type);
        if (checkPosition(horizontal, vertical))
        {
            try
            {
                game->dropPiece(pieceType, shogi::Position(horizontal, vertical));
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

int Game::countPieces(const shogi::PieceType pieceType, const shogi::Player &player, const shogi::ListOfPieces &pieces) const
{
    shogi::Piece samplePiece(pieceType,player);
    return std::count_if(pieces.begin(), pieces.end(), [&samplePiece](shogi::Piece *piece){ return piece->equals(samplePiece);});
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

    shogi::JSONSaveManager *saveManager = new shogi::JSONSaveManager();
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
    shogi::JSONSaveManager *saveManager = nullptr;
    try
    {
        saveManager = new shogi::JSONSaveManager(JSONSaveString);
        game->load(saveManager);
    }
    catch(std::exception &e)
    {
        std::cout << "Save is bad" << std::endl;
        return false;
    }
    save.close();

    std::cout << "Loaded!" << std::endl;

    delete saveManager;
    return true;
}




























