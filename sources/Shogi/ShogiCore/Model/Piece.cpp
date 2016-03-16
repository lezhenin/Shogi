#include "Piece.h"


Piece::Piece(PieceType pt, Player pl, Square *sq): ptype(pt), player(pl), sq(sq)
{
    //todo simplify construction
    if (this->ptype >= Rook)
    {
        this->bePromoted = true;
    }
    else
    {
        this->bePromoted = false;
    }
    if (this->ptype >= PromotedRook)
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
        this->ptype=PieceType((int)(this->ptype)+PROMOTION_STEP);
    }
}

void Piece::unPromote()
{
    if(this->bePromoted && this->promoted)
    {

        this->ptype=PieceType((int)(this->ptype)-PROMOTION_STEP);
    }
}

void Piece::setSquare(Square *sq)
{
    this->sq=sq;
}

void Piece::setPlayer(Player pl)
{
    this->player=pl;
}

Piece::~Piece()
{

}


