#ifndef SHOGI_MATE_H
#define SHOGI_MATE_H

#include "GameSituation.h"

class Mate : public GameSituation
{

public:
    virtual std::string getMessage() override;

    Mate() : GameSituation() { endOfGame = true;}
};


#endif //SHOGI_MATE_H
