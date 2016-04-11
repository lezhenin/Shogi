
#ifndef SHOGI_PROMOTIONISAVAIBLE_H
#define SHOGI_PROMOTIONISAVAIBLE_H
#include "GameSituation.h"
#include "../../ShogiGameAPI.h"

/**
 * @brief Игровая ситуация "Возможен переворт фигуры"
 */
class PromotionIsAvailable : public GameSituation
{

public:

    PromotionIsAvailable(ShogiGameAPI *game, const Position &position) : game(game), position(position) { executable = true; }

    std::string getMessage()
    {
        return "You can promote piece.";
    }

    void execute()
    {
        try
        {
            game->promotePiece(position);
        }
        catch (std::exception &e)
        {
            throw e;
        }

    }
private:
    ShogiGameAPI *game;
    Position position;
};


#endif //SHOGI_PROMOTIONISAVAIBLE_H
