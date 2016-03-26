#ifndef SHOGI_ABSTRACTBOARDMEMENTO_H
#define SHOGI_ABSTRACTBOARDMEMENTO_H

#include "AbstractBoard.h"

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
};


#endif //SHOGI_ABSTRACTBOARDMEMENTO_H
