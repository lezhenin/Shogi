#ifndef SHOGI_GAMELOADER_H
#define SHOGI_GAMELOADER_H


#include "AbstractGameLoader.h"

class GameLoader: public AbstractGameLoader
{
public:

    virtual void loadGame(const Save &save, AbstractBoard &board);
    virtual void loadGame(AbstractBoard &board);

};

#endif //SHOGI_GAMELOADER_H
