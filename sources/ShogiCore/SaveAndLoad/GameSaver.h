#ifndef SHOGI_GAMESAVER_H
#define SHOGI_GAMESAVER_H

#include "AbstractGameSaver.h"

class GameSaver : public AbstractGameSaver
{

public:
    virtual Save saveGame(AbstractBoard &board);

};


#endif //SHOGI_GAMESAVER_H
