#ifndef SHOGI_SHAH_H
#define SHOGI_SHAH_H

#include "GameSituation.h"
/**
 * @brief Игровая ситуация "Шах"
 */
class Shah : public GameSituation
{
public:
    Shah(): GameSituation(){}
    std::string getMessage() const
    {
        return "Shah!";
    }

};


#endif //SHOGI_SHAH_H
