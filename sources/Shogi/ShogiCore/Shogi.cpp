#include "Shogi.h"

Shogi::Shogi()
{

}

void Shogi::initGame()
{
    Piece *p = new Piece(Rook,Sente,0);
    this->board.setPiece(p,Position(5,3));
    this->board.getPiecesOnBoard().push_back(p);
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
}

void Shogi::promotePiece(const Position &position)
{
    this->board.getPiece(position)->promote();
}

void Shogi::dropPiece(const PieceType pt, const Position &position)
{
    Piece  *p = new Piece(pt,Sente);
    this->getBoard().getSenteCapturedPieces().push_back(p);

    Pieces * cap = &this->getBoard().getSenteCapturedPieces();
    for( unsigned int i = 0; i<cap->size(); i++)
    {
        if((*cap)[i]->getType()==pt)
        {
            this->board.setPiece((*cap)[i],position);
            this->board.getPiecesOnBoard().push_back((*cap)[i]);
        }
    }

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

}

