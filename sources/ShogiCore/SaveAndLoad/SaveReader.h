#ifndef SHOGI_SAVEREADER_H
#define SHOGI_SAVEREADER_H

#include <vector>
#include "../Model/Piece.h"
#include "Block.h"

/**
 * @brief Интерфейс для чтения сохранений.
 *
 */
class SaveReader
{
public:
     /**
     * @brief Получит список фигур, стоящих на доске.
     *
     * @return Вектор объектов типа Block,
     * которые хронят информацию о фигурах.
     */
    virtual std::vector<Block> getPiecesOnBoard() = 0;
    /**
     * @brief Получит список захваченных фигур.
     *
     * @param player Игрок, захваченные фигуры
     * которые необходимо получить.
     *
     * @return Вектор объектов типа PieceType,
     * соответсвующих типам захваченных фигур.
     */
    virtual std::vector<PieceType> getCapturedPieces(const Player &player) = 0;
    /**
     * @brief Получить игрока, которому
     * принадлежит текущий ход.
     */
    virtual Player &getCurrentPlayer() = 0;
};



#endif //SHOGI_SAVEREADER_H
