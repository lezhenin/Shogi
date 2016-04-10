#ifndef SHOGI_SAVEREADER_H
#define SHOGI_SAVEREADER_H

#include <vector>
#include "../../Model/Piece.h"
#include "Block.h"


class SaveReader
{
public:
    virtual std::vector<Block> getPiecesOnBoard() = 0;
    virtual std::vector<PieceType> getCapturedPieces(Player player) = 0;
};


#endif //SHOGI_SAVEREADER_H
