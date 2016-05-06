#include "Piece.h"
#include "Exceptions/PieceIsNotOnBoardException.h"

using namespace shogi;

Piece::Piece(const PieceType pieceType, const Player &player, Square *square) noexcept : pieceType(pieceType), player(player), square(square)
{
    if (this->pieceType >= Rook)
    {
        this->bePromoted = true;
    }
    else
    {
        this->bePromoted = false;
    }
    if (this->pieceType >= PromotedRook)
    {
        this->promoted=true;
    }
    else
    {
        this->promoted=false;
    }

}

PieceType Piece::getType() const noexcept
{
    return this->pieceType;
}

Square *Piece::getSquare() const noexcept
{
    return this->square;
}

Player Piece::getPlayer() const noexcept
{
    return this->player;
}

Position &Piece::getPosition() const
{
    if (this->getSquare() == nullptr)
    {
        throw PieceIsNotOnBoardException();
    }
    return this->getSquare()->getPosition();
}

bool Piece::wasPromoted() const noexcept
{
    return this->promoted;
}

bool Piece::canBePromoted() const noexcept
{
    return this->bePromoted;
}

void Piece::promote() noexcept
{
    if(this->bePromoted && !this->promoted)
    {
        this->pieceType = PieceType((int)(this->pieceType) + PROMOTION_STEP);
        promoted = true;
    }
}

void Piece::unPromote() noexcept
{
    if(this->bePromoted && this->promoted)
    {

        this->pieceType = PieceType((int)(this->pieceType) - PROMOTION_STEP);
        promoted = false;
    }
}

void Piece::setSquare(Square *square) noexcept
{
    this->square = square;
}

void Piece::setPlayer(const Player &player) noexcept
{
    this->player = player;
}


bool Piece::equals(const Piece &piece) const noexcept
{
    return (player == piece.player && pieceType == piece.pieceType);
}




