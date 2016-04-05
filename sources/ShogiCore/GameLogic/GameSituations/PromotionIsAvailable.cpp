#include "PromotionIsAvailable.h"

std::string PromotionIsAvailable::getMessage() {
    return "You can promote piece.";
}

void PromotionIsAvailable::execute()
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



