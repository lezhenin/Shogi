#ifndef SHOGI_BOARDMEMENTO_H
#define SHOGI_BOARDMEMENTO_H

#include "AbstractBoard.h"
#include "Board.h"
#include <vector>
/**
 * @brief Структура содержащая фигуру и клетку
 *
 * Структура содеражащая пару значений: указатель
 * на клетку доски и указатель на фигуру.
 */
struct Pair
{
    Piece* piece;
    Square* square;
};
/**
 * @brief Реализция паттерна Мементо для модели доски.
 *
 * Класс сохраняющий внутреннее состояние объекта класса
 * Board и способный восстановить его при необходимости.
 */
class BoardMemento
{

public:
    /**
     * @brief Конструктор
     *
     * Сохраняет текущее состояние доски.
     * @param[in] board Указатель на доску
     */
    explicit BoardMemento(Board *board);
    /**
     * @brief Восстановить состояние доски.
     *
     * Восстанавливает сохраненное сотстояние доски.
     */
    void restore();
    /**
     * @brief Деструктор
     */
    virtual ~BoardMemento();



private:
    Board * board;
    std::vector<Pair> pairs;
    ListOfPieces senteCaptured;
    ListOfPieces goteCaptured;
};


#endif //SHOGI_BOARDMEMENTO_H
