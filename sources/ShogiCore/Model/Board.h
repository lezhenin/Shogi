#ifndef BOARD_H
#define BOARD_H
#include "AbstractBoard.h"
typedef std::list<Piece*> ListOfPieces;

/// Игровая модель доски с фигурами
class Board: public AbstractBoard
{
public:

    Board(int w = BOARD_WIDTH, int h = BOARD_WIDTH);

    void setPiece(Piece *piece, const Position &pos);
    void removePiece(const Position &pos);

    Piece *getPiece(const Position &pos);

    ListOfPieces &getPiecesOnBoard();
    ListOfPieces &getSenteCapturedPieces();
    ListOfPieces &getGoteCapturedPieces();

    ~Board();
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
