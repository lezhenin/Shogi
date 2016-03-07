#ifndef BOARD_H
#define BOARD_H
#include "Square.h"
#include "vector"

typedef std::vector<Piece> Pieces;

class Board
{
public:

    Board(int w, int h);
    ~Board();
private:

    Square ***squares;
    Pieces onBoard;
    Pieces SenteCaptured;
    Pieces GoteCaptured;

    int width;
    int height;
};

#endif // BOARD_H
