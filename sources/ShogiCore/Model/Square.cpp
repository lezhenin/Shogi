#include "Square.h"

Square::Square(const Position &position, Piece *piece): position(position), piece(piece){}

Position &Square::getPosition()
{
    return this->position;
}

Piece *Square::getPiece() const
{
    return this->piece;
}

void Square::setPiece(Piece *piece)
{
    this->piece=piece;
}

