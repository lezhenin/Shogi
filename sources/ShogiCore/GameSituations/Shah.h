#ifndef SHOGI_SHAH_H
#define SHOGI_SHAH_H

#include "GameSituation.h"

class Shah : public GameSituation
{
public:
    Shah(): GameSituation(){};
    std::string getMessage();
};


#endif //SHOGI_SHAH_H
