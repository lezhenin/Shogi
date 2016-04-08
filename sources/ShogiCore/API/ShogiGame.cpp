#include <algorithm>
#include "ShogiGame.h"
#include "../GameLogic/GameSituations/PromotionIsAvailable.h"
#include "../GameLogic/GameSituations/Mate.h"
#include "../GameLogic/GameSituations/Shah.h"

void ShogiGame::initGame()
{
    gameLoader->loadGame(*board);
}

ShogiGame::ShogiGame()
{
    board = new Board();
    gameLogic = new ShogiGameLogic(board);
    gameLoader = new GameLoader();
    gameSaver = new GameSaver();
}

ShogiGame::~ShogiGame()
{
    delete board;
    delete gameLogic;
    delete gameLoader;
    delete gameSaver;
}

AbstractBoard &ShogiGame::getBoard() {
    return *board;
}

void ShogiGame::pickPiece(const Position &position)
{
    Piece * piece = this->board->getPiece(position);

    if( piece == nullptr)
    {
        throw std::exception();
    }

    if(piece->getPlayer() != currentPlayer)
    {
        throw std::exception();
    }

    this->pickedPiece = piece;
}

void ShogiGame::unPickPiece()
{
    this->pickedPiece = nullptr;
}

void ShogiGame::movePiece(const Position &position)
{
    if(pickedPiece == nullptr)
    {
        throw std::exception();
    }
    if(!this->gameLogic->checkMove(this->pickedPiece,position))
    {
        throw std::exception();
    }
    Piece* piece = this->board->getPiece(position);
    if(piece != nullptr)
    {
        piece->unPromote();
        piece->setPlayer(currentPlayer);
        this->board->getCapturedPieces(currentPlayer).push_back(piece);
        this->board->removePiece(position);
    }

    this->board->removePiece(pickedPiece->getPosition());
    this->board->setPiece(pickedPiece,position);

    if(gameLogic->checkShah(transformPlayer(currentPlayer)))
    {
        gameSituations.push(std::shared_ptr<GameSituation>(new Shah()));
        if(gameLogic->checkMate(transformPlayer(currentPlayer)))
        {
            gameSituations.push(std::shared_ptr<GameSituation>(new Mate()));
        }
    }
    if(gameLogic->checkPromotion(pickedPiece))
    {
        gameSituations.push(std::shared_ptr<GameSituation>(new PromotionIsAvailable(this,position)));
    }
    unPickPiece();
    currentPlayer = transformPlayer(currentPlayer);
}

Player ShogiGame::transformPlayer(Player player) const
{
    return (Player)(((int)player+1)%2);
}

void ShogiGame::promotePiece(const Position &position)
{
    if(this->board->getPiece(position) == nullptr)
    {
        throw std::exception();
    }
    if(!gameLogic->checkPromotion(this->board->getPiece(position)))
    {
        throw std::exception();
    }
    this->board->getPiece(position)->promote();
}

void ShogiGame::dropPiece(const PieceType pt, const Position &position)
{
    Piece tmp(pt,currentPlayer);
    ListOfPieces::iterator it = std::find_if(board->getCapturedPieces(currentPlayer).begin(),board->getCapturedPieces(currentPlayer).end(),
                                             std::bind1st(std::mem_fun(&Piece::equals),&tmp));
    if(it == board->getCapturedPieces(currentPlayer).end())
    {
        throw std::exception();
    }
    Piece *piece = *it;

    if(!gameLogic->checkDrop(piece,position))
    {
        throw std::exception();
    }
    board->getCapturedPieces(currentPlayer).remove(piece);
    board->setPiece(piece, position);

    currentPlayer = transformPlayer(currentPlayer);
}

ListOfGameSituations &ShogiGame::getGameSituation()
{
    return gameSituations;
}

Player ShogiGame::getCurrentPlayer()
{
    return currentPlayer;
}

