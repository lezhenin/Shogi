#ifndef BOARD_H
#define BOARD_H
#include "SquareIsEmptyException.h"
#include "Square.h"
#include <vector>

typedef std::vector<Piece*> Pieces;

/// Игровая модель доски с фигурами
class Board
{
public:

    ///Конструктор
    Board(int w = BOARD_WIDTH, int h = BOARD_WIDTH);

    /// Метод, позволяющий установить фигуру на доску
    void setPiece(Piece *piece, const Position &pos);
    /// Метод, позволяющий удалить фигуру с доски
    void removePiece(const Position &pos);

    /// Метод, позволяющий получить указатель на фигуру по позиции на доске
    Piece *getPiece(const Position &pos);

    /// Метод, позволяющий получить указатели на все фигуры на доске
    Pieces &getPiecesOnBoard();
    /// Метод, позволяющий получить указатели на все фигуры, захваченные сторооной Sente
    Pieces &getSenteCapturedPieces();
    /// Метод, позволяющий получить указатели на все фигуры, захваченные сторооной Gote
    Pieces &getGoteCapturedPieces();

    ///Деструктор
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
