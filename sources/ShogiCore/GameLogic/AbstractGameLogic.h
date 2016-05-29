#ifndef SHOGI_ABSTRACTSHOGIGAMELOGIC_H
#define SHOGI_ABSTRACTSHOGIGAMELOGIC_H

#include <map>
#include <vector>
#include <list>
#include "Direction.h"
#include "../Model/AbstractBoard.h"

namespace shogi
{
    /**
     * @brief Абстрактный класс, содержащий игровую логику и правила игры.
     */
    class AbstractGameLogic
    {
    public:

        /**
		 * @brief Проверить возможность хода.
		 *
		 * @param piece Фигура, ход который будет проверяться.
		 * @param pos   Позиция, ход в которую будет проверяться.
		 * @return true если ход возможен, false если ход не возможен.
		 */
        virtual bool checkMove(const Piece *piece, const Position &pos) const noexcept = 0;

        /**
		 * @brief Проверить постановку шаха.
		 *
		 * @param player Игрок, постановка шаха которому будет проверяться.
		 * @return true если шах поставлен, false если шах не поставлен.
		 */
        virtual bool checkShah(const Player &player) const = 0;

        /**
		 * @brief Проверить постановку мата.
		 *
		 * @param player Игрок, постановка мата которому будет проверяться.
		 * @return true если мат поставлен, false если мат не поставлен.
		 */
        virtual bool checkMate(const Player &player) const = 0;

        /**
		 * @brief Проверить возможность переворта.
		 *
		 * @param piece Фигура, возможность переворота которой будет проверяться.
		 * @return true если переворот возможен, false если переворот не возможен.
		 */
        virtual bool checkPromotion(const Piece *piece) const noexcept = 0;

        /**
		 * @brief Проверить возможность постановки ранее захваченной фигуры на доску.
		 *
		 * @param piece Фигура, возможность постановки которой будет проверяться.
		 * @param pos Позиция, куда будет выставляться фигура.
		 * @return true если постановка возможна, false если постановка не возможна.
		 */
        virtual bool checkDrop(Piece *piece, const Position &position) const noexcept = 0;

        /**
         * @Получить все возможоные ходы для данной фигуры.
         */
        virtual std::vector<Position> getAllPositionToMove(const Piece *piece) const noexcept = 0;
        virtual ~AbstractGameLogic() { }
    };
}

#endif //SHOGI_ABSTRACTSHOGIGAMELOGIC_H
