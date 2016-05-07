#include <algorithm>
#include "Shogi.h"
#include "Exceptions/BadMoveException.h"

using namespace shogi;

void Shogi::load() noexcept
{
    gameLoader->loadGame(*board, &currentPlayer);
}

Shogi::Shogi() noexcept
{
    board = new Board();
    gameLogic = new GameLogic(board);
    gameLoader = new GameLoader();
    gameSaver = new GameSaver();
}

Shogi::~Shogi() noexcept
{
    clearToRedo();
    clearToUndo();
    delete board;
    delete gameLogic;
    delete gameLoader;
    delete gameSaver;
}

AbstractBoard &Shogi::getBoard() const noexcept
{
    return *board;
}

void Shogi::pickPiece(const Position &position)
{
    Piece * piece = this->board->getPiece(position);

    if( piece == nullptr)
    {
        throw BadPickException("Square is empty");
    }

    if(piece->getPlayer() != currentPlayer)
    {
        throw BadPickException("Piece don't belong you.");
    }

    this->pickedPiece = piece;
}

void Shogi::unPickPiece() noexcept
{
    this->pickedPiece = nullptr;
}

void Shogi::movePiece(const Position &destination)
{
    if(pickedPiece == nullptr)
    {
        throw BadMoveException("Piece was not picked.");
    }
    if(!this->gameLogic->checkMove(this->pickedPiece, destination))
    {
        throw BadMoveException("Illegal move.");
    }

    toUndo.push(board->getMemento());
    clearToRedo();

    capturePiece(destination);

    this->board->removePiece(pickedPiece->getPosition());
    this->board->setPiece(pickedPiece, destination);

    checkShahMateGameSituations();
    checkPromoteGameSituation(destination);

    unPickPiece();
    currentPlayer.changePlayer();
}

void Shogi::promotePiece(const Position &position)
{
    if(this->board->getPiece(position) == nullptr)
    {
        throw BadPromoteException("Square is empty.");
    }
    if(!gameLogic->checkPromotion(this->board->getPiece(position)))
    {
        throw BadPromoteException("Illegal promotion.");
    }
    this->board->getPiece(position)->promote();
    checkShahMateGameSituations();
}

void Shogi::dropPiece(const PieceType pieceType, const Position &position)
{
    Piece *piece = board->findPiece(pieceType, currentPlayer, board->getCapturedPieces(currentPlayer));
    if (piece == nullptr)
    {
        throw BadDropException("Piece was not captured.");
    }

    if(!gameLogic->checkDrop(piece, position))
    {
        throw BadDropException("Illegal drop.");
    }

    toUndo.push(board->getMemento());
    clearToRedo();

    board->getCapturedPieces(currentPlayer).remove(piece);
    board->setPiece(piece, position);

    currentPlayer.changePlayer();
}

ListOfGameSituations &Shogi::getGameSituation() noexcept
{
    return gameSituations;
}

bool Shogi::undo() noexcept
{
    if(!toUndo.empty())
    {
        toRedo.push(board->getMemento());
        board->setMemento(toUndo.top());
        delete toUndo.top();
        toUndo.pop();
        currentPlayer.changePlayer();
        return true;
    }
    return false;
}

bool Shogi::redo() noexcept
{
    if(!toRedo.empty())
    {
        toUndo.push(board->getMemento());
        board->setMemento(toRedo.top());
        delete toRedo.top();
        toRedo.pop();
        currentPlayer.changePlayer();
        return true;
    }
    return false;
}

Player Shogi::getCurrentPlayer () const noexcept
{
    return currentPlayer;
}

void Shogi::clearToUndo() noexcept
{

    while(!toUndo.empty())
    {
        delete toUndo.top();
        toUndo.pop();
    }
}

void Shogi::clearToRedo() noexcept
{
    while(!toRedo.empty())
    {
        delete toRedo.top();
        toRedo.pop();
    }
}

void Shogi::checkPromoteGameSituation(const Position &position) noexcept
{
    if(gameLogic->checkPromotion(pickedPiece))
    {
        gameSituations.push(std::shared_ptr<GameSituation>(new PromotionIsAvailable(this,position)));
    }
}

void Shogi::checkShahMateGameSituations() noexcept
{
    if(gameLogic->checkShah(currentPlayer.nextPlayer()))
    {
        gameSituations.push(std::shared_ptr<GameSituation>(new Shah()));
        if(gameLogic->checkMate(currentPlayer.nextPlayer()))
        {
            gameSituations.push(std::shared_ptr<GameSituation>(new Mate()));
        }
    }
}

void Shogi::capturePiece(const Position &position) noexcept
{
    Piece* piece = this->board->getPiece(position);
    if(piece != nullptr && piece->getPlayer() != currentPlayer)
    {
        piece->unPromote();
        piece->setPlayer(currentPlayer);
        this->board->getCapturedPieces(currentPlayer).push_back(piece);
        this->board->removePiece(position);
    }
}

void Shogi::save(SaveWriter *saveWriter) noexcept
{
    gameSaver->saveGame(saveWriter,*board,&currentPlayer);
}

void Shogi::load(SaveReader *saveReader) noexcept
{
    clearToRedo();
    clearToUndo();
    clearBoard(*board);
    gameLoader->loadGame(saveReader,*board,&currentPlayer);
}

void Shogi::clearBoard(AbstractBoard &board) noexcept
{
    for (Piece *piece : board.getAllPieces())
    {
        if (piece->getSquare() != nullptr)
        {
            piece->getSquare()->setPiece(nullptr);
        }
        delete piece;
    }
    board.getAllPieces().clear();
    board.getPiecesOnBoard().clear();
    board.getCapturedPieces(Sente).clear();
    board.getCapturedPieces(Gote).clear();
}

const Piece *Shogi::getPickedPiece() const noexcept
{
    return pickedPiece;
}











































