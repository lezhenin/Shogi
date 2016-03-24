#ifndef SHOGI_SHAH_H
#define SHOGI_SHAH_H

#include "GameSituation.h"

class Shah : public GameSituation
{
public:
    virtual std::string getMessage() override;

    Shah(): GameSituation(){};

};


#endif //SHOGI_SHAH_H
