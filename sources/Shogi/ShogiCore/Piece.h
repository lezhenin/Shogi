#ifndef PIECE_H
#define PIECE_H
#include "enumirations.h"
#include "Square.h"

class Square;

class Piece
{
public:

    Piece(PieceType pt, Square *sq);

    inline PieceType getType() const;
    inline Square *getSquare() const;

    inline bool wasPromoted() const;
    inline bool canBePromoted() const;

    void promote();
    void unPromote();

    void setSquare(Square *sq);

    ~Piece();

private:

    PieceType ptype;
    Square *sq;
    bool promoted;
    bool bePromoted;
};

#endif // PIECE_H
