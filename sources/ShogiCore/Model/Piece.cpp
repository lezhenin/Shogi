#include "Piece.h"


Piece::Piece(const PieceType pieceType, const Player &player, Square *square): pieceType(pieceType), player(player), square(square)
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

PieceType Piece::getType() const
{
    return this->pieceType;
}

Square *Piece::getSquare() const
{
    return this->square;
}

Player Piece::getPlayer() const
{
    return this->player;
}

Position &Piece::getPosition() const
{
    return this->getSquare()->getPosition();
}

bool Piece::wasPromoted() const
{
    return this->promoted;
}

bool Piece::canBePromoted() const
{
    return this->bePromoted;
}

void Piece::promote()
{
    if(this->bePromoted && !this->promoted)
    {
        this->pieceType = PieceType((int)(this->pieceType) + PROMOTION_STEP);
    }
}

void Piece::unPromote()
{
    if(this->bePromoted && this->promoted)
    {

        this->pieceType = PieceType((int)(this->pieceType) - PROMOTION_STEP);
    }
}

void Piece::setSquare(Square *square)
{
    this->square = square;
}

void Piece::setPlayer(const Player &player)
{
    this->player = player;
}


bool Piece::equals(Piece *piece) {
    return (player == piece->player && pieceType == piece->pieceType);
}




