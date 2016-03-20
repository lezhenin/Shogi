#ifndef PIECE_H
#define PIECE_H
#include "Square.h"

class Square;

const int PROMOTION_STEP = 10;
/**
 * @enum Player
 * Содержит значения соответсвующие играющим сторонам
 */
enum Player{
    Sente=0, Gote
};
/**
 * @enum PieceType
 * Содержит типы сущестсвующих фигур, включая перевернутые фигуры.
 */
enum PieceType{
    King=2, GoldGeneral, Rook, Bishop, SilverGeneral, Knight, Lance, Pawn,
    PromotedRook=Rook+PROMOTION_STEP, PromotedBishop, PromotedSilverGeneral,  PromotedKnight, PromotedLance, PromotedPawn,
};

/**
 * @brief Модель фигуры
 */
class Piece
{
public:

    /**
     * @brief Конструктор
     * @param[in] pt Тип фигуры.
     * @param[in] pl Игрок которому принадлежит фигура.
     * @param[in] sq Клетка на которой находится фигура.
     */
    Piece(PieceType pt, Player pl, Square *sq=nullptr);
    /**
     * @brief Получить тип фигуры.
     * @return Тип фигуры
     */
    PieceType getType() const;
    /**
     * @brief Получить игрока.
     * @return Значение соответсвующие игроку,
     * которому принадлежит фигура
     */
    Player getPlayer() const;
    /**
     * @brief Получить позицию фигуры.
     * @return Позиция, где находится фигура
     */
    Position &getPosition() const;
    /**
     * @brief Получить клетку.
     * @return Клетка, на которой находится фигура
     */
    Square *getSquare() const;
    /**
     * @brief Узнать переврнута ли фигура.
     * @return true или false
     */
    bool wasPromoted() const;
    /**
     * @brief Узнать может ли быть переврнута фигура.
     * @return true или false
     */
    bool canBePromoted() const;
    /**
     * @brief Перевернуть фигуру.
     *  Меняет тип фигуры если это возможно.
     */
    void promote();
    /**
     * @brief Отменить переворот фигуры.
     *  Меняет тип фигуры если это возможно.
     **/
    void unPromote();
    /**
     * @brief Установить клетку
     *  Устанавливает клетку на которой находится фигура.
     */
    void setSquare(Square *sq);
    /**
     * @brief Установить игрока
     *  Устанавливает игрока, которому принадлежит фигура.
     */
    void setPlayer(Player pl);
    /**
     * @brief Деструктор
     */
    ~Piece();


private:

    PieceType ptype;
    Player player;
    Square *sq;

    bool promoted;
    bool bePromoted;

};





#endif // PIECE_H
