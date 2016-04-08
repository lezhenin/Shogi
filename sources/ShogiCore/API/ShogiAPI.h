#ifndef GAMECORE_H
#define GAMECORE_H

#include "ShogiGameAPI.h"



/**
 * @brief Игровой интерфейс.
 */
class ShogiAPI
{

public:

    /**
     * @brief Инициализировать игру.
     * Устанавливает фигуры на доске.
     */
    virtual void initGame()=0;
    /**
     *
     */
    virtual Player getCurrentPlayer() = 0;
    /**
     * @brief Переместить фигуру.
     * Перемещает раннее выбранную фигуру.
     * @param[in] position Позиция куда необходимо перместить фигур.
     */
    virtual void movePiece(const Position &from, const Position& to)=0;
    /**
     * @brief Перевернуть фигуру.
     * Переворачивает фигуру.
     * @param[in] position Позиция фигуры, которую необходимо превернуть.
    */
    virtual void promotePiece(const Position& position)=0;
    /**
     * @brief Устанвоить фигуру.
     * Устанавливает фигуру из захваченных одной из сторон.
     * @param[in] pt       Тип устанавливаемой фигуры.
     * @param[in] position Позиция фигуры, куда нужно установить фиугру.
    */
    virtual void dropPiece(const PieceType pt, const Position& position)=0;
    /**
     * @brief Получть доску.
     * @return Указатель на доску с фигурами.
     */
    virtual AbstractBoard &getBoard()=0;
    /**
     * @brief Получть статус игры.
     * @return Список игровых ситуаций
     */
    virtual ListOfGameSituations &getGameSituation()=0;

    virtual void undo()=0;


    virtual ~ShogiAPI(){};
};

#endif // GAMECORE_H
