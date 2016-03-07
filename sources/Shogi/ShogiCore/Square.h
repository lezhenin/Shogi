#ifndef SQUARE_H
#define SQUARE_H
#include "Position.h"
#include "Piece.h"

class Piece;

class Square
{
public:

    Square(Position pos, Piece *piece);

    inline Position getPosition() const;
    inline Piece *getPiece() const;

    void setPiece (Piece *p);

    ~Square();

private:

    Position pos;
    Piece *piece;

};

#endif // SQUARE_H
