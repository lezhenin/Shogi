#ifndef GAMECORE_H
#define GAMECORE_H

#include <vector>
#include <memory>
#include <queue>
#include "GameLogic/GameSituations/GameSituation.h"
#include "Model/Position.h"
#include "Model/Board.h"

using ListOfGameSituations = std::queue<std::shared_ptr<GameSituation>>;

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
     * @brief Узнать какому игрку принадлежит очередность хода.
     *
     * @return Игрок, который совершает ход в данный момент.
     */
    virtual Player getCurrentPlayer() = 0;
    /**
     * @brief Выбрать фигуру.
     * Созраняет фигуру для дальнейших действий.
     * @param position Позиция фигуры.
     */
    virtual void pickPiece(const Position& position)=0;
    /**
     * @brief Отменить выбор фигуры.
     */
    virtual void unPickPiece()=0;
    /**
     * @brief Переместить фигуру.
     * Перемещает раннее выбранную фигуру.
     * @param position Позиция куда необходимо перместить фигур.
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
     * @brief Отмена хода
     *
     * Возвращает доску к тому состоянию, которое
     * было до совершения предыдущего хода.
     */
    virtual void undo()=0;
    /**
     * @brief Возврат хода
     *
     * Возвращает доску к тому состоянию, которое
     * было до отмены предыдущего хода.
     */
    virtual void redo()=0;
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

    virtual ~ShogiGameAPI(){};
};

#endif // GAMECORE_H
