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
    clearToRedo();
    clearToUndo();
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
    clearToRedo();

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

Player Shogi::transformPlayer(Player player) const
{
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

    Piece *piece = *it;

    if(!gameLogic->checkDrop(piece,position))
    {
        throw std::exception();
    }

    toUndo.push(board->getMemento());
    clearToRedo();

    board->getCapturedPieces(currentPlayer).remove(piece);
    board->setPiece(piece, position);

    currentPlayer = transformPlayer(currentPlayer);
}

ListOfGameSituations &Shogi::getGameSituation()
{
    return gameSituations;
}

void Shogi::undo()
{
    if(!toUndo.empty())
    {
        toRedo.push(board->getMemento());
        board->setMemento(toUndo.top());
        delete toUndo.top();
        toUndo.pop();
        currentPlayer = transformPlayer(currentPlayer);
    }
}

void Shogi::redo()
{
    if(!toRedo.empty())
    {
        toUndo.push(board->getMemento());
        board->setMemento(toRedo.top());
        delete toRedo.top();
        toRedo.pop();
        currentPlayer = transformPlayer(currentPlayer);
    }
}

Player Shogi::getCurrentPlayer()
{
    return currentPlayer;
}

void Shogi::clearToUndo()
{

    while(!toUndo.empty())
    {
        delete toUndo.top();
        toUndo.pop();
    }
}

void Shogi::clearToRedo()
{
    while(!toRedo.empty())
    {
        delete toRedo.top();
        toRedo.pop();
    }
}































