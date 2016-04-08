#ifndef SHOGI_DROP_H
#define SHOGI_DROP_H


#include "Command.h"

class Drop : public Command
{

public:
    Drop(ShogiAPI *game, PieceType pieceType, int h, int v) : game(game), pieceType(pieceType), position(h,v) { }
    virtual void execute() override
    {
        try
        {
            game->dropPiece(pieceType, position);
        }
        catch(std::exception &e)
        {
            throw e;
        }
    }

private:
    ShogiAPI *game;
    Position position;
    PieceType pieceType;
};


#endif //SHOGI_DROP_H
