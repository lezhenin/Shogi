
#ifndef SHOGI_PROMOTIONISAVAIBLE_H
#define SHOGI_PROMOTIONISAVAIBLE_H
#include "GameSituation.h"
#include "../../API/ShogiAPI.h"

/**
 * @brief Игровая ситуация "Возможен переворт фигуры"
 */
class PromotionIsAvailable : public GameSituation
{

public:

    PromotionIsAvailable(ShogiGameAPI *game, const Position &position) : game(game), position(position) { executable = true; }

    std::string getMessage();
    void execute();
private:
    ShogiGameAPI *game;
    Position position;
};


#endif //SHOGI_PROMOTIONISAVAIBLE_H
