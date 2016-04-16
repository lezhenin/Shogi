#ifndef GAMECORE_H
#define GAMECORE_H

#include <vector>
#include <memory>
#include <queue>
#include "../GameLogic/GameSituations/GameSituation.h"
#include "../Model/Position.h"
#include "../Model/Board.h"
#include "../SaveAndLoad/SaveWriter.h"
#include "../SaveAndLoad/SaveReader.h"

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
    virtual Player getCurrentPlayer() const = 0 ;

    /**
     * @brief Выбрать фигуру.
     * Сохраняет фигуру для дальнейших действий.
     * @param position Позиция фигуры.
     */
    virtual void pickPiece(const Position& position) = 0;

    /**
     * @brief Отменить выбор фигуры.
     */
    virtual void unPickPiece()=0;

    /**
     * @brief Переместить фигуру.
     * Перемещает раннее выбранную фигуру.
     * @param position Позиция куда необходимо переместить фигуру.
     */
    virtual void movePiece(const Position& position)=0;

    /**
     * @brief Перевернуть фигуру.
     * Переворачивает фигуру.
     * @param[in] position Позиция фигуры, которую необходимо перевернуть.
    */
    virtual void promotePiece(const Position& position)=0;

    /**
     * @brief Установить фигуру.
     * Устанавливает фигуру из захваченных одной из сторон.
     * @param[in] pt       Тип устанавливаемой фигуры.
     * @param[in] position Позиция, куда нужно установить фигуру.
    */
    virtual void dropPiece(const PieceType pieceType, const Position& position)=0;

    /**
     * @brief Отмена хода
     *
     * Возвращает доску к тому состоянию, которое
     * было до совершения предыдущего хода.
     */
    virtual bool undo() = 0;

    /**
     * @brief Возврат хода
     *
     * Возвращает доску к тому состоянию, которое
     * было до отмены предыдущего хода.
     */
    virtual bool redo() = 0;
    /**
    * @brief Сохранить игру
    *
    * Сохранят игру, используя интерфейс
    * SaveWriter.
    */
    virtual void save(SaveWriter *saveWriter) = 0;
    /**
     * @brief Загрузить игру
     *
     * Загружает игру, используя интерфейс
     * SaveReader.
     */
    virtual void load(SaveReader *saveReader) = 0;

    /**
     * @brief Получить доску.
     * @return Указатель на доску с фигурами.
     */
    virtual AbstractBoard &getBoard() const = 0;

    /**
     * @brief Получить статус игры.
     * @return Список игровых ситуаций
     */
    virtual ListOfGameSituations &getGameSituation() = 0;

    virtual ~ShogiGameAPI(){}
};

#endif // GAMECORE_H
