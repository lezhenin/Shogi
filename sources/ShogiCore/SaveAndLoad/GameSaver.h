#ifndef SHOGI_GAMESAVER_H
#define SHOGI_GAMESAVER_H

#include "WritersAndReaders/SaveWriter.h"
#include "../Model/AbstractBoard.h"

class GameSaver
{
public:

    void saveGame(SaveWriter *saveWriter, AbstractBoard &board);

};


#endif //SHOGI_GAMESAVER_H
