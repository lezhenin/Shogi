#ifndef SHOGI_BOARDMEMENTO_H
#define SHOGI_BOARDMEMENTO_H

#include "Board.h"
#include <vector>

namespace shogi
{
    class Board;

    /**
     * @brief Структура содержащая инфорамацию о фигуре.
     *
     * Структа содержит указатель на фигуру,
     * клетку на которой она стоит и информацию
     * о том, перевернута ли фиугура.
     */
    struct PieceInfo
    {
        Piece *piece;
        Square *square;
        Player player;
        bool promote = false;
    };


    /**
     * @brief Реализция паттерна Мементо для модели доски.
     *
     */
    class BoardMemento : public AbstractBoardMemento
    {

    public:

        /**
		 * @brief Конструктор
		 *
		 * Сохраняет текущее состояние доски.
		 * @param[in] board Указатель на доску
		 */
        explicit BoardMemento(Board *board) noexcept;

    private:
        friend class Board;

        void restore() noexcept override;

    public:
        virtual ~BoardMemento() noexcept { }


    private:
        Board *board;
        std::vector<PieceInfo> pairs;
        std::map<Player, ListOfPieces> capturedPieces;
    };
}

#endif //SHOGI_BOARDMEMENTO_H
