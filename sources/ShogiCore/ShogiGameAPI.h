#ifndef SHOGI_SHOGIGAMEAPI_H
#define SHOGI_SHOGIGAMEAPI_H

#include <vector>
#include <memory>
#include <queue>
#include "GameLogic/GameSituations/GameSituation.h"
#include "Model/Position.h"
#include "Model/Board.h"

using ListOfGameSituations = std::queue<std::shared_ptr<GameSituation>>;

class ShogiGameAPI
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
     * @brief Выбрать фигуру.
     * Созраняет фигуру для дальнейших действий.
     * @param[in] position Позиция фигуры.
     */
    virtual void pickPiece(const Position& position)=0;
    /**
     * @brief Отменить выбор фигуры.
     */
    virtual void unPickPiece()=0;
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
    virtual AbstractBoard &getBoard()=0;
    /**
     * @brief Получть статус игры.
     * @return Список игровых ситуаций
     */
    virtual ListOfGameSituations &getGameSituation()=0;


    virtual ~ShogiGameAPI() { }
};


#endif //SHOGI_SHOGIGAMEAPI_H
