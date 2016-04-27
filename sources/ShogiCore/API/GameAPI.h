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
		 * @return Игрок, который совершает ход в данный момент.
		 */
		virtual Player getCurrentPlayer() const noexcept = 0;

        /**
         * @brief Получить выбранную фигуру.
         */
		virtual const Piece* getPickedPiece() const noexcept = 0;

		/**
		 * @brief Выбрать фигуру.
		 * Сохраняет фигуру для дальнейших действий.
		 * @param position Позиция фигуры.
		 */
		virtual void pickPiece(const Position &position) = 0;

		/**
		 * @brief Отменить выбор фигуры.
		 */
		virtual void unPickPiece() noexcept = 0;

		/**
		 * @brief Переместить фигуру.
		 * Перемещает раннее выбранную фигуру.
		 * @param position Позиция куда необходимо переместить фигуру.
		 */
		virtual void movePiece(const Position &position) = 0;

		/**
		 * @brief Перевернуть фигуру.
		 * Переворачивает фигуру.
		 * @param[in] position Позиция фигуры, которую необходимо перевернуть.
		*/
		virtual void promotePiece(const Position &position) = 0;

		/**
		 * @brief Установить фигуру.
		 * Устанавливает фигуру из захваченных одной из сторон.
		 * @param[in] pt       Тип устанавливаемой фигуры.
		 * @param[in] position Позиция, куда нужно установить фигуру.
		*/
		virtual void dropPiece(const PieceType pieceType, const Position &position) = 0;

		/**
		 * @brief Отмена хода
		 *
		 * Возвращает доску к тому состоянию, которое
		 * было до совершения предыдущего хода.
		 */
		virtual bool undo() noexcept = 0;

		/**
		 * @brief Возврат хода
		 *
		 * Возвращает доску к тому состоянию, которое
		 * было до отмены предыдущего хода.
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
		 * @return Указатель на доску с фигурами.
		 */
		virtual AbstractBoard &getBoard() const noexcept = 0;

		/**
		 * @brief Получить статус игры.
		 * @return Список игровых ситуаций
		 */
		virtual ListOfGameSituations &getGameSituation() noexcept = 0;

		virtual ~GameAPI() noexcept { }
	};

}
#endif // GAMECORE_H
