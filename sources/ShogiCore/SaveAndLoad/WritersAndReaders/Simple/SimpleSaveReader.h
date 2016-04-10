
#ifndef SHOGI_SIMPLESAVEREADER_H
#define SHOGI_SIMPLESAVEREADER_H


#include "SimpleSave.h"
#include "../SaveReader.h"

class SimpleSaveReader : public SaveReader
{

public:
    explicit SimpleSaveReader(SimpleSave *save) : save(save) { }

private:
    virtual std::vector<Block> getPiecesOnBoard()
    {
        return save->onBoard;
    }

    virtual std::vector<PieceType> getCapturedPieces(Player player)
    {
        if(player == Sente)
        {
            return save->senteCaptured;
        }
        else
        {
            return save->goteCaptured;
        }
    }

private:
    SimpleSave *save;
};


#endif //SHOGI_SIMPLESAVEREADER_H
