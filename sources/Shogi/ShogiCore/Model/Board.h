#ifndef BOARD_H
#define BOARD_H
#include "BoardInterface.h"
typedef std::vector<Piece*> Pieces;

/// Игровая модель доски с фигурами
class Board: public BoardInterface
{
public:

    Board(int w = BOARD_WIDTH, int h = BOARD_WIDTH);

    void setPiece(Piece *piece, const Position &pos);
    void removePiece(const Position &pos);

    Piece *getPiece(const Position &pos);

    Pieces &getPiecesOnBoard();
    Pieces &getSenteCapturedPieces();
    Pieces &getGoteCapturedPieces();

    ~Board();
private:

    Square ***squares;
    Pieces onBoard;
    Pieces SenteCaptured;
    Pieces GoteCaptured;

    int width;
    int height;

    Square *getSquare(const Position &pos);
};

#endif // BOARD_H
