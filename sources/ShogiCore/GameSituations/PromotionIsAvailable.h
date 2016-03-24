
#ifndef SHOGI_PROMOTIONISAVAIBLE_H
#define SHOGI_PROMOTIONISAVAIBLE_H
#include "GameSituation.h"

class PromotionIsAvailable : public GameSituation
{

public:
    PromotionIsAvailable():GameSituation() { }
    std::string getMessage();

};


#endif //SHOGI_PROMOTIONISAVAIBLE_H
