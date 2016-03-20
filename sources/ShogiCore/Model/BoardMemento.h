#ifndef SHOGI_BOARDMEMENTO_H
#define SHOGI_BOARDMEMENTO_H

#include "AbstractBoard.h"
#include <vector>

struct Pair
{
    Piece* piece;
    Square* square;
};

class BoardMemento
{

public:
    explicit BoardMemento(AbstractBoard *board);

    virtual ~BoardMemento();

    void restore();

private:
    AbstractBoard * board;
    std::vector<Pair> pairs;
    ListOfPieces senteCaptured;
    ListOfPieces goteCaptured;
};


#endif //SHOGI_BOARDMEMENTO_H
