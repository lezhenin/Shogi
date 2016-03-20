#ifndef SQUARE_H
#define SQUARE_H
#include "../Position.h"
#include "Piece.h"

class Piece;
/// Игровая модель клетки доски
class Square
{
public:
    ///Конструктор
    Square(Position pos, Piece *piece = nullptr);

    ///Метод, позволяющий получить позицую клетки на доске
    Position &getPosition();
    ///Метод, позволяющий получить фигуру, которая находится на данной клетке
    Piece *getPiece() const;
    ///Метод, позволяющий устнавоить фигуру на клетку
    void setPiece (Piece *p);
    ///Деструктор
    ~Square();

private:

    Position pos;
    Piece *piece;

};

#endif // SQUARE_H
