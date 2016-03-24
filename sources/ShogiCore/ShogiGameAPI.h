#ifndef GAMECORE_H
#define GAMECORE_H

#include <vector>
#include "GameSituations/GameSituation.h"
#include "Position.h"
#include "Model/Board.h"


/**
 * @brief Игровой интерфейс.
 */
class ShogiGameAPI
{

public:

    /**
     * @brief Инициализировать игру.
     * Устанавливает фигуры на доске.
     */
    virtual void initGame()=0;
    /**
     * @brief Выбрать фигуру.
     * Созраняет фигуру для дальнейших действий.
     * @param[in] position Позиция фигуры.
     */
    virtual void pickPiece(const Position& position)=0;
    /**
     * @brief Переместить фигуру.
     * Перемещает раннее выбранную фигуру.
     * @param[in] position Позиция куда необходимо перместить фигур.
     */
    virtual void movePiece(const Position& position)=0;
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
    virtual Board &getBoard()=0;
    /**
     * @brief Получть статус игры.
     * @return /todo status
     */
    virtual std::vector<GameSituation> getGameSituation()=0;
};

#endif // GAMECORE_H
