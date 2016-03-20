#ifndef BOARD_H
#define BOARD_H
#include "AbstractBoard.h"

/**
 * @brief Модель доски
 * */
class Board: public AbstractBoard
{
public:

    Board(int w = BOARD_WIDTH, int h = BOARD_HEIGHT);

    void setPiece(Piece *piece, const Position &pos);
    void removePiece(const Position &pos);

    Piece *getPiece(const Position &pos);

    ListOfPieces &getPiecesOnBoard();
    ListOfPieces &getSenteCapturedPieces();
    ListOfPieces &getGoteCapturedPieces();

    ~Board();

    static const int BOARD_WIDTH = 9;
    static const int BOARD_HEIGHT = 9;

private:

    Square ***squares;
    ListOfPieces onBoard;
    ListOfPieces SenteCaptured;
    ListOfPieces GoteCaptured;

    int width;
    int height;

    Square *getSquare(const Position &pos);
};

#endif // BOARD_H
