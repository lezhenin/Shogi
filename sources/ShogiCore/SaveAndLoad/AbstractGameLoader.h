#ifndef SHOGI_ABSTRACTGAMELOADER_H
#define SHOGI_ABSTRACTGAMELOADER_H


#include "Save.h"
#include "../Model/AbstractBoard.h"
/**
 * @brief Интерфейс класса, позволяющего загружать
 * ранее сохраненную игру.
 */
class AbstractGameLoader
{

public:
    virtual void loadGame(AbstractBoard &board) = 0;
    virtual void loadGame(const Save &save, AbstractBoard &board) = 0;
};


#endif //SHOGI_ABSTRACTGAMELOADER_H
