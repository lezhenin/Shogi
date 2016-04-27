#ifndef SHOGI_SAVEWRITER_H
#define SHOGI_SAVEWRITER_H

#include "../Model/Piece.h"

namespace shogi
{
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
        virtual void addPieceOnBoard(const PieceType pieceType, const Player &player, const Position &position) noexcept = 0;
        /**
		 * @brief Добавляет захваченную фигуру
		 * на доске в объект сохранения.
		 */
        virtual void addCapturedPiece(const Player &player, const PieceType pieceType) noexcept = 0;
        /**
		 * @brief Установить игрка.
		 *
		 * Устанавливает игрока, которому
		 * принадлежит ход.
		 */
        virtual void setCurrentPlayer(const Player &player) noexcept = 0;
    };
}

#endif //SHOGI_SAVEWRITER_H
