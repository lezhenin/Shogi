#ifndef ENUMIRATIONS
#define ENUMIRATIONS
#include "constants.h"
enum PieceType{
    King=0, GoldGeneral, Rock, Bishop, SilverGeneral, Knight, Lance, Pawn,
    PromotedRock=Rock+PROMOTION_STEP, PromotedBishop, PromotedSilverGeneral,  PromotedKnight, PromotedLance, PromotedPawn,
};
#endif // ENUMIRATIONS

