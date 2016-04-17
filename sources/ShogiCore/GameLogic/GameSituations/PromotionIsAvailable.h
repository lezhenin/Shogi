#ifndef SHOGI_PROMOTIONISAVAIBLE_H
#define SHOGI_PROMOTIONISAVAIBLE_H

#include "GameSituation.h"
#include "../../API/GameAPI.h"

namespace shogi
{
    /**
     * @brief Игровая ситуация "Возможен переворт фигуры"
     */
    class PromotionIsAvailable : public GameSituation
    {

    public:

        PromotionIsAvailable(GameAPI *game, const Position &position) : game(game), position(position)
        {
            executable = true;
        }

        std::string getMessage() const
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
                throw;
            }

        }

    private:
        GameAPI *game;
        Position position;
    };
}

#endif //SHOGI_PROMOTIONISAVAIBLE_H
