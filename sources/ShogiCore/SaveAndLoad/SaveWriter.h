#ifndef SHOGI_SAVEWRITER_H
#define SHOGI_SAVEWRITER_H

#include "../Model/Piece.h"

/**
 * @brief Интерфейс для создания сохранений.
 *
 */
class SaveWriter
{
public:
    /**
     * @brief Добавляет фигуру стоящую
     * на доске в объект сохранения.
     */
    virtual void addPieceOnBoard(PieceType pieceType, Player player, Position position) = 0;
    /**
     * @brief Добавляет захваченную фигуру
     * на доске в объект сохранения.
     */
    virtual void addCapturedPiece(Player player, PieceType pieceType) = 0;
    /**
     * @brief Установить игрка.
     *
     * Устанавливает игрока, которому
     * принадлежит ход.
     */
    virtual void setCurrentPlayer(Player player) = 0;
};


#endif //SHOGI_SAVEWRITER_H
