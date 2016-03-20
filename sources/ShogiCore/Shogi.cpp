#include "Shogi.h"
#include <algorithm>


void Shogi::initGame()
{
    Piece *p = new Piece(Rook,Sente,0);
    this->board.setPiece(p,Position(5,3));
}

void Shogi::pickPiece(const Position &position)
{
    Piece* p = this->board.getPiece(position);
    if(p!=nullptr)
    {
        this->pickedPiece = p;
    }
}

void Shogi::movePiece(const Position &position)
{
    if(pickedPiece != nullptr)
    {
        this->board.removePiece(pickedPiece->getPosition());
        this->board.setPiece(pickedPiece,position);

    }
    pickedPiece = nullptr;
}

void Shogi::promotePiece(const Position &position)
{
    this->board.getPiece(position)->promote();
}

void Shogi::dropPiece(const PieceType pt, const Position &position)
{
    Piece  *p = new Piece(pt,Sente);
    this->getBoard().getSenteCapturedPieces().push_back(p);

    ListOfPieces * cap = &this->getBoard().getSenteCapturedPieces();
    for(ListOfPieces::iterator it = cap->begin(); it != cap->end(); ++it)
    {
        if((*it)==p)
        {
            this->board.setPiece((*it),position);
        }
    }
    cap->remove(p);

}

Board &Shogi::getBoard()
{
    return this->board;
}

void Shogi::getGameStatus()
{

}

Shogi::~Shogi()
{
    for(Piece *piece: this->board.getPiecesOnBoard()){
        delete piece;
    }
}

