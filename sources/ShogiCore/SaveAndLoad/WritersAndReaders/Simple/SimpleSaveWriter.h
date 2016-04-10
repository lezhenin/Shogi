
#ifndef SHOGI_SIMPLESAVEWRITER_H
#define SHOGI_SIMPLESAVEWRITER_H


#include "../SaveWriter.h"
#include "SimpleSave.h"
#include "../Block.h"

class SimpleSaveWriter : public SaveWriter
{

public:
    virtual void addPieceOnBoard(PieceType pieceType, Player player, Position position) override
    {
        save.onBoard.push_back(Block(pieceType, player, position));
    }
    virtual void addCapturedPiece(Player player, PieceType pieceType) override
    {
        if(player == Sente)
        {
            save.senteCaptured.push_back(pieceType);
        }
        if(player == Gote)
        {
            save.goteCaptured.push_back(pieceType);
        }
    }
    SimpleSave *getSimpleSave()
    {
        return &save;
    }

private:
    SimpleSave save;
};


#endif //SHOGI_SIMPLESAVEWRITER_H
