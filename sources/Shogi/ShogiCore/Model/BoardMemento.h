#ifndef SHOGI_BOARDMEMENTO_H
#define SHOGI_BOARDMEMENTO_H

#include "BoardInterface.h"

struct Pair
{
    Piece* piece;
    Square* square;
};

class BoardMemento
{

public:
    explicit BoardMemento(BoardInterface &board);

    virtual ~BoardMemento();

    void restore();

private:
    BoardInterface& board;
    std::vector<Pair> pairs;
    Pieces senteCaptured;
    Pieces goteCaptured;
};


#endif //SHOGI_BOARDMEMENTO_H
