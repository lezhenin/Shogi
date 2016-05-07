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

namespace shogi
{
	using ListOfGameSituations = std::queue<std::shared_ptr<GameSituation>>;

	/**
 	 * @brief Игровой интерфейс.
  	 */
	class GameAPI
	{

	public:


		/**
		 * @brief Узнать какому игрку принадлежит очередность хода.
		 *
		 * Игрок устанавливается и переключается автоматически по
		 * ходу игры.
		 *
		 * @return Игрок, который совершает ход в данный момент.
		 */
		virtual Player getCurrentPlayer() const noexcept = 0;

        /**
         * @brief Получить выбранную фигуру.
         *
         * Если фигура не выбрана то реущльтатом будет nullptr.
         *
         * @return Константный указатель на выбранную фигуру.
         */
		virtual const Piece* getPickedPiece() const noexcept = 0;

		/**
		 * @brief Выбрать фигуру.
		 *
		 * Сохраняет фигуру для дальнейших действий.
		 *
		 * В случае указания позоции не находящейся на доске будет
		 * выброшено исключение BadPositionException.
		 *
		 * В случае, если фигуру выбрать не возможно, будет выброшено
		 * исключение типа BadPickException с уточняющим сообщением.
		 *
		 * @param position Позиция фигуры.
		 */
		virtual void pickPiece(const Position &position) = 0;

		/**
		 * @brief Отменить выбор фигуры.
		 */
		virtual void unPickPiece() noexcept = 0;

		/**
		 * @brief Переместить фигуру.
		 *
		 * Перемещает раннее выбранную фигуру.
		 *
		 * В случае запрещенного хода будет выброшено исключение
		 * типа BadMoveException с уточняющим сообщением.
		 *
		 * В случае указания позоции не находящейся на доске будет
		 * выброшено исключение BadPositionException.
		 *
		 * Если на клетке стоит вражеская фигура, то она будет съедена,
		 * автоматически убрана из списка фигур на доске и помещена в
		 * список захваченных фигу, при этом переворот фигуры будет
		 * отменен, если она была перевернуто до съедения.
		 *
		 * После окончания перемещения формируются сообщения о текущих
		 * игровых ситуациях и помещаются в соответсующий список. Также
		 * происходит смена игрока.
		 *
		 * @param position Позиция куда необходимо переместить фигуру.
		 */
		virtual void movePiece(const Position &position) = 0;

		/**
		 * @brief Перевернуть фигуру.
		 *
		 * Переворачивает фигуру.
		 *
		 * В случае запрещенного переворота будет выброшено исключение
		 * типа BadPromoteException с уточняющим сообщением.
		 *
		 * В случае указания позоции не находящейся на доске будет
		 * выброшено исключение BadPositionException.
		 *
		 * После окончания переворта формируются сообщения о текущих
		 * игровых ситуациях и помещаются в соответсующий список.
		 *
		 * Не рекомендуется вызывать метод самостоятельно, при
		 * возможности перворта в список игровых ситуаций будет
		 * помещен объект PromotionIsAvailable, метод execute() которого
		 * выполнит все необходимые действия.
		 *
		 * @param[in] position Позиция фигуры, которую необходимо перевернуть.
		*/
		virtual void promotePiece(const Position &position) = 0;

		/**
		 * @brief Установить фигуру.
		 *
		 * Устанавливает фигуру из захваченных одной из сторон.
		 *
		 * В случае, если фигуру не возможно выставить на доску
		 * будет выброшено исключение типа BadPromoteException
		 * с уточняющим сообщением.
		 *
		 * В случае указания позоции не находящейся на доске будет
		 * выброшено исключение BadPositionException.
		 *
		 * После установки фигуры на доску, фигура будет пермещена
		 * из списка захваченных фигур в список фигур, находящихся
		 * на доске.
		 *
		 * @param[in] pt       Тип устанавливаемой фигуры.
		 * @param[in] position Позиция, куда нужно установить фигуру.
		*/
		virtual void dropPiece(const PieceType pieceType, const Position &position) = 0;

		/**
		 * @brief Отмена хода
		 *
		 * Возвращает доску к тому состоянию, которое
		 * было до совершения предыдущего хода.
		 *
		 * @return true если удалось выполнить отмену
		 * и false если нет ходов для отмены.
		 */
		virtual bool undo() noexcept = 0;

		/**
		 * @brief Возврат хода
		 *
		 * Возвращает доску к тому состоянию, которое
		 * было до отмены предыдущего хода.
		 *
		 * @return true если удалось выполнить отмену
		 * и false если нет ходов для отмены.
		 */
		virtual bool redo() noexcept = 0;

		/**
		 * @brief Сохранить игру
		 *
		 * Сохранят игру, используя интерфейс
		 * SaveWriter.
		 */
		virtual void save(SaveWriter *saveWriter) noexcept = 0;

		/**
		 * @brief Загрузить игру
		 *
		 * Загружает игру, используя интерфейс
		 * SaveReader.
		 */
		virtual void load(SaveReader *saveReader) noexcept = 0;

		/**
		 * @brief Загружает игру.
		 *
		 * Устанавливает фигуры на доске, в соотвевтсвии
		 * с начальной растановкой.
		 */
		virtual void load() noexcept = 0;

		/**
		 * @brief Получить доску.
		 *
		 * Позволяет получить объект содержащий
		 * игровую модель доски.
		 *
		 * @return Ссылка на доску с фигурами.
		 */
		virtual AbstractBoard &getBoard() const noexcept = 0;

		/**
		 * @brief Получить статус игры.
		 *
		 * Возвращет список объектов GameSituations.
		 * Список выполняет интерфейс очереди(queue) и
		 * его можно модифицировать.
		 *
		 * @return Ссылку на список игровых ситуаций.
		 */
		virtual ListOfGameSituations &getGameSituation() noexcept = 0;

		virtual ~GameAPI() noexcept { }
	};

}
#endif // GAMECORE_H
