#ifndef SHOGI_SIMPLESAVEMANAGER_H
#define SHOGI_SIMPLESAVEMANAGER_H

#include "../SaveReader.h"
#include "../SaveWriter.h"
#include "SimpleSave.h"

class SimpleSaveManager : public SaveReader, public SaveWriter
{

public:

    explicit SimpleSaveManager(const SimpleSave &save) : save(save) { }
    SimpleSaveManager() { }

    virtual std::vector<Block> getPiecesOnBoard();
    virtual std::vector<PieceType> getCapturedPieces(Player player);
    virtual void addPieceOnBoard(PieceType pieceType, Player player, Position position);
    virtual void addCapturedPiece(Player player, PieceType pieceType);
    SimpleSave *getSimpleSave()
    {
     return &save;
    }

private:
    SimpleSave save;
};


#endif //SHOGI_SIMPLESAVEMANAGER_H
