#ifndef SHOGI_GAMELOADER_H
#define SHOGI_GAMELOADER_H


#include "../Model/AbstractBoard.h"
#include "SaveWriter.h"
#include "SaveReader.h"

class GameLoader
{
public:

    virtual void loadGame(SaveReader *saveReader, AbstractBoard &board);
    virtual void loadGame(AbstractBoard &board);

};

#endif //SHOGI_GAMELOADER_H
