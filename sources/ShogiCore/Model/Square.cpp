#include "Square.h"

Square::Square(Position pos, Piece *piece): pos(pos), piece(piece){}

Position &Square::getPosition()
{
    return this->pos;
}

Piece *Square::getPiece() const
{
    return this->piece;
}

void Square::setPiece(Piece *p)
{
    this->piece=p;
}

//TODO: зачем нам нужен невиртуальный деструктор, и почему тело не в .h
Square::~Square()
{

}

