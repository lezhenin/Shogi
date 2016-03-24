
#ifndef SHOGI_PROMOTIONISAVAIBLE_H
#define SHOGI_PROMOTIONISAVAIBLE_H
#include "GameSituation.h"

class PromotionIsAvailable : GameSituation
{

public:
private:
    virtual std::string getMessage() override;

    PromotionIsAvailable() : GameSituation() { }
};


#endif //SHOGI_PROMOTIONISAVAIBLE_H
