#include <algorithm>
#include "Shogi.h"


void Shogi::initGame()
{
    gameLoader->loadGame(*board);
}

Shogi::Shogi()
{
    board = new Board();
    gameLogic = new ShogiGameLogic(board);
    gameLoader = new GameLoader();
    gameSaver = new GameSaver();
}

Shogi::~Shogi()
{
    while(!toUndo.empty())
    {
        delete toUndo.top();
        toUndo.pop();
    }
    delete board;
    delete gameLogic;
    delete gameLoader;
    delete gameSaver;
}

AbstractBoard &Shogi::getBoard() {
    return *board;
}

void Shogi::pickPiece(const Position &position)
{
    if(this->board->getPiece(position) == nullptr )
    {
        throw std::exception();
    }
    if(this->board->getPiece(position)->getPlayer() != currentPlayer)
    {
        throw std::exception();
    }
    this->pickedPiece = this->board->getPiece(position);
}

void Shogi::unPickPiece()
{
    this->pickedPiece = nullptr;
}

void Shogi::movePiece(const Position &position)
{
    if(pickedPiece == nullptr)
    {
        throw std::exception();
    }
    if(!this->gameLogic->checkMove(this->pickedPiece,position))
    {
        throw std::exception();
    }
    toUndo.push(board->getMemento());
    if(this->board->getPiece(position) != nullptr)
    {
        this->board->getPiece(position)->unPromote();
        this->board->getPiece(position)->setPlayer(currentPlayer);
        this->board->getCapturedPieces(currentPlayer).push_back(this->board->getPiece(position));
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

Player Shogi::transformPlayer(Player player) const {
    return (Player)(((int)player+1)%2);
}

void Shogi::promotePiece(const Position &position)
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

void Shogi::dropPiece(const PieceType pt, const Position &position)
{
    Piece tmp(pt,currentPlayer);
    ListOfPieces::iterator it = std::find_if(board->getCapturedPieces(currentPlayer).begin(),board->getCapturedPieces(currentPlayer).end(),
                     std::bind1st(std::mem_fun(&Piece::equals),&tmp));
    if(it == board->getCapturedPieces(currentPlayer).end())
    {
        throw std::exception();
    }
    Piece *ptr = *it;

    if(!gameLogic->checkDrop(ptr,position))
    {
        throw std::exception();
    }
    toUndo.push(board->getMemento());
    board->getCapturedPieces(currentPlayer).remove(ptr);
    board->setPiece(ptr, position);
    currentPlayer = transformPlayer(currentPlayer);
}

ListOfGameSituations &Shogi::getGameSituation()
{
    return gameSituations;
}

void Shogi::undo()
{
    board->setMemento(toUndo.top());
    delete toUndo.top();
    toUndo.pop();
}

void Shogi::redo()
{

}

























