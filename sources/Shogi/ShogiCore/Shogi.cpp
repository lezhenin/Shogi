#include "Shogi.h"

Shogi::Shogi()
{
    this->board = new Board(BOARD_HEIGHT,BOARD_WIDTH);
}

Shogi::~Shogi()
{
    delete this->board;
}

