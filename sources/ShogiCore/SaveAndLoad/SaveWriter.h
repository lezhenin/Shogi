#ifndef SHOGI_SAVEWRITER_H
#define SHOGI_SAVEWRITER_H


#include "../Model/Piece.h"

class SaveWriter
{
public:
    virtual void addPieceOnBoard(PieceType pieceType, Player player, Position position) = 0;
    virtual void addCapturedPiece(Player player, PieceType pieceType) = 0;
};


#endif //SHOGI_SAVEWRITER_H
