#ifndef SHOGI_BOARDMEMENTO_H
#define SHOGI_BOARDMEMENTO_H

#include "Board.h"
#include <vector>

class Board;

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
class BoardMemento : public AbstractBoardMemento
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
     * @brief Деструктор
     */
    virtual ~BoardMemento();

private:
    friend class Board;
    /**
     * @brief Восстановить состояние доски.
     *
    * Восстанавливает сохраненное сотстояние доски.
    */
    void restore();



private:
    Board * board;
    std::vector<Pair> pairs;
    ListOfPieces senteCaptured;
    ListOfPieces goteCaptured;
};


#endif //SHOGI_BOARDMEMENTO_H
