#ifndef PIECE_H
#define PIECE_H
#include "enumirations.h"
#include "Square.h"

class Square;
/// Модель фигуры
class Piece
{
public:

    Piece(PieceType pt, Player pl, Square *sq=nullptr);

    PieceType getType() const;
    Player getPlayer() const;
    Position &getPosition() const;

    inline bool wasPromoted() const;
    inline bool canBePromoted() const;

    void promote();
    void unPromote();

    void setSquare(Square *sq);
    void setPlayer(Player pl);

    ~Piece();

private:

    PieceType ptype;
    Player player;
    Square *sq;

    bool promoted;
    bool bePromoted;

    Square *getSquare() const;
};

#endif // PIECE_H
