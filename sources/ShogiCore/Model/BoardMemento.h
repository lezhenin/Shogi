#ifndef SHOGI_BOARDMEMENTO_H
#define SHOGI_BOARDMEMENTO_H

#include "Board.h"
#include <vector>

class Board;
using Pair = std::pair<Piece*,Square*>;

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
    std::vector<Pair> pairs;
    std::map<Player,ListOfPieces> capturedPieces;
};


#endif //SHOGI_BOARDMEMENTO_H
