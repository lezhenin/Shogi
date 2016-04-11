#ifndef SHOGI_BLOCK_H
#define SHOGI_BLOCK_H


#include "../Model/Piece.h"

class Block
{
public:
    Block(PieceType pieceType, Player player, const Position &position) : pieceType(pieceType), player(player),
                                                                          position(position) { }

    PieceType pieceType;
    Player player;
    Position position;
};


#endif //SHOGI_BLOCK_H