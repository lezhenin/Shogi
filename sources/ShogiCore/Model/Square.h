#ifndef SQUARE_H
#define SQUARE_H
#include "Position.h"
#include "Piece.h"

class Piece;

/**
 * @brief Игровая модель клетки доски
 */
class Square
{
public:
    /**
     * @brief Конструктор
     *
     * @param[in] pos   Позиция клетки на доскею.
     * @param[in] piece Фигура, которая находится на это клетке.
     */
    Square(Position pos, Piece *piece = nullptr);
    /**
     * @brief Получить позицию клетки на доске.
     *
     * @return Позиция клетки
     */
    Position &getPosition();
    /**
     * @brief Получить фигуру.
     *
     * @return Фигура, которая находится на данной клетке.
     */
    Piece *getPiece() const;
    /**
     * @brief Установить фигуру.
     *
     * Устанавливает фигуру на данную клетку
     */
    void setPiece (Piece *p);
    /**
     * @brief Деструктор
     */
    ~Square();

private:

    Position pos;
    Piece *piece;

};

#endif // SQUARE_H
