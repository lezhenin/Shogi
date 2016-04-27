#include "Square.h"

using namespace shogi;

Square::Square(const Position &position, Piece *piece) noexcept : position(position), piece(piece){}

Position &Square::getPosition() noexcept
{
    return this->position;
}

Piece *Square::getPiece() const noexcept
{
    return this->piece;
}

void Square::setPiece(Piece *piece) noexcept
{
    this->piece = piece;
}

