#ifndef SHOGIGAMELOGIC_H
#define SHOGIGAMELOGIC_H
#include "Board.h"

class ShogiGameLogic
{
public:
    explicit ShogiGameLogic(Board *b = 0);

private:
    Board *board;
};

#endif // SHOGIGAMELOGIC_H
