#ifndef SHOGI_H
#define SHOGI_H
#include "ShogiAPI.h"


class Shogi : public ShogiAPI
{
public:

    Shogi();

    void initGame();

    ~Shogi();

private:

    Board *board;
    ShogiGameLogic game;
};

#endif // SHOGI_H
