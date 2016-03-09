#ifndef SHOGI_H
#define SHOGI_H
#include "ShogiAPI.h"

class Shogi: ShogiAPI
{
public:

    Shogi();

    void initGame();
    void pickPiece(Position& position);
    void movePiece(Position& position);
    void promotePiece(Position& position);
    void dropPiece(PieceType pt);

    Board &getBoard();
    void getGameStatus();

    ~Shogi();

private:

    Board board{BOARD_HEIGHT,BOARD_WIDTH};
};

#endif // SHOGI_H
