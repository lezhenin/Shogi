#ifndef SHOGI_MATE_H
#define SHOGI_MATE_H

#include "GameSituation.h"
/**
 * @brief Игровая ситуация "Мат"
 */
class Mate : public GameSituation
{

public:
    Mate() : GameSituation() { endOfGame = true;}
    std::string getMessage();
};


#endif //SHOGI_MATE_H
