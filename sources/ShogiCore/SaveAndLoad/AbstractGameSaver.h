#ifndef SHOGI_ABSTRACTGAMESAVER_H
#define SHOGI_ABSTRACTGAMESAVER_H

#include "Save.h"
#include "../Model/AbstractBoard.h"

/**
 * @brief Интерфейс класса, позволяющего сохранять игру.
 */
class AbstractGameSaver
{
public:
    virtual Save saveGame(AbstractBoard &board) = 0;
};


#endif //SHOGI_ABSTRACTGAMESAVER_H
