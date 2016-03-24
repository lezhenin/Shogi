
#ifndef SHOGI_PROMOTIONISAVAIBLE_H
#define SHOGI_PROMOTIONISAVAIBLE_H
#include "GameSituation.h"
/**
 * @brief Игровая ситуация "Возможен переворт фигуры"
 */
class PromotionIsAvailable : public GameSituation
{

public:
    PromotionIsAvailable():GameSituation() { }
    std::string getMessage();

};


#endif //SHOGI_PROMOTIONISAVAIBLE_H
