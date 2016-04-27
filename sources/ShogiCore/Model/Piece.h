#ifndef PIECE_H
#define PIECE_H

#include "Square.h"
#include "Player.h"

namespace shogi
{
    class Square;

    const int PROMOTION_STEP = 10;

    /**
     * @enum PieceType
     * Содержит типы сущестсвующих фигур, включая перевернутые фигуры.
     */
    enum PieceType
    {
        King = 2,
        GoldGeneral,
        Rook,
        Bishop,
        SilverGeneral,
        Knight,
        Lance,
        Pawn,
        PromotedRook = Rook + PROMOTION_STEP,
        PromotedBishop,
        PromotedSilverGeneral,
        PromotedKnight,
        PromotedLance,
        PromotedPawn
    };

    /**
     * @brief Модель фигуры
     */
    class Piece
    {
    public:

        /**
		 * @brief Конструктор
		 *
		 * @param[in] pt Тип фигуры.
		 * @param[in] pl Игрок, которому принадлежит фигура.
		 * @param[in] sq Клетка, на которой находится фигура.
		 */
        Piece(const PieceType pieceType, const Player &player, Square *square = nullptr) noexcept;

        /**
		 * @brief Получить тип фигуры.
		 *
		 * @return Тип фигуры
		 */
        PieceType getType() const noexcept;

        /**
		 * @brief Получить игрока.
		 *
		 * @return Значение соответсвующие игроку,
		 * которому принадлежит фигура
		 */
        Player getPlayer() const noexcept;

        /**
		 * @brief Получить позицию фигуры.
		 *
		 * @return Позиция, где находится фигура
		 */
        Position &getPosition() const;

        /**
		 * @brief Получить клетку.
		 *
		 * @return Клетка, на которой находится фигура
		 */
        Square *getSquare() const noexcept;

        /**
		 * @brief Узнать переврнута ли фигура.
		 *
		 * @return true или false
		 */
        bool wasPromoted() const noexcept;

        /**
		 * @brief Узнать может ли быть переврнута фигура.
		 *
		 * @return true или false
		 */
        bool canBePromoted() const noexcept;

        /**
		 * @brief Перевернуть фигуру.
		 *
		 *  Меняет тип фигуры если это возможно.
		 */
        void promote() noexcept;

        /**
		 * @brief Отменить переворот фигуры.
		 *
		 *  Меняет тип фигуры если это возможно.
		 **/
        void unPromote() noexcept;

        /**
		 * @brief Установить клетку
		 *
		 *  Устанавливает клетку на которой находится фигура.
		 */
        void setSquare(Square *square) noexcept;

        /**
		 * @brief Установить игрока
		 *
		 *  Устанавливает игрока, которому принадлежит фигура.
		 */
        void setPlayer(const Player &player) noexcept;

        /**
		 * @brief Узнать эквивалентны ли фигуры.
		 *
		 * Фигуры эквиваленты в том случае если их тип и сторона,
		 * которой они принадлежат свопадают.
		 * @param piece Фигура для сравнения.
		 * @return true если фигуры эквивалентны, false если нет.
		 */
        bool equals(Piece *piece) const noexcept;

        /**
		 * @brief Деструктор
		 */
        virtual ~Piece() noexcept { };


    private:

        PieceType pieceType;
        Player player;
        Square *square;

        bool promoted;
        bool bePromoted;

    };
}




#endif // PIECE_H
