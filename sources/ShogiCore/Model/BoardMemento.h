#ifndef SHOGI_BOARDMEMENTO_H
#define SHOGI_BOARDMEMENTO_H

#include "Board.h"
#include <vector>

class Board;
/**
 * @brief Структура содержащая инфорамацию о фигуре.
 *
 * Структа содержит указатель на фигуру,
 * клетку на которой она стоит и информацию
 * о том, перевернута ли фиугура.
 */
struct PieceInfo
{
    Piece* piece;
    Square *square;
    bool promote = false;
};


/**
 * @brief Реализция паттерна Мементо для модели доски.
 *
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

private:
    friend class Board;
    void restore();

public:
    virtual ~BoardMemento() { }


private:
    Board * board;
    std::vector<PieceInfo> pairs;
    std::map<Player,ListOfPieces> capturedPieces;
};


#endif //SHOGI_BOARDMEMENTO_H
