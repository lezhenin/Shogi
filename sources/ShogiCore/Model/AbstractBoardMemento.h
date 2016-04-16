#ifndef SHOGI_ABSTRACTBOARDMEMENTO_H
#define SHOGI_ABSTRACTBOARDMEMENTO_H

#include "AbstractBoard.h"

namespace shogi
{
    /**
     * @brief Интерфейс паттерна Мементо.
     * Класс сохраняющий внутреннее состояние объекта класса
     * Board и способный восстановить его при необходимости.
     */
    class AbstractBoardMemento
    {
    public:

    private:
        friend class AbstractBoard;

        /**
		 * @brief Восстановить состояние доски.
		 *
		 * Восстанавливает сохраненное сотстояние доски.
		 */
        virtual void restore() = 0;

    public:
        virtual ~AbstractBoardMemento() { }
    };
}

#endif //SHOGI_ABSTRACTBOARDMEMENTO_H
