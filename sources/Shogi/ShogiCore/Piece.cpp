#include "Piece.h"
#include "enumirations.h"

Piece::Piece(PieceType pt, Square *sq): ptype(pt), sq(sq)
{
    if (this->ptype >= Rock)
    {
        this->bePromoted = true;
    }
    else
    {
        this->bePromoted = false;
    }
    if (this->ptype >= PromotedRock)
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
    return this->ptype;
}

Square *Piece::getSquare() const
{
    return this->sq;
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
        this->ptype=PieceType((int)(this->ptype)+PROMOTION_STEP);
}

void Piece::unPromote()
{
    if(this->bePromoted && this->promoted)
        this->ptype=PieceType((int)(this->ptype)-PROMOTION_STEP);
}

void Piece::setSquare(Square *sq)
{
    this->sq=sq;
}

Piece::~Piece()
{

}


