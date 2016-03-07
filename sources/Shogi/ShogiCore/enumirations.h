#ifndef ENUMIRATIONS
#define ENUMIRATIONS
#include "constants.h"

enum PieceType{
    King=2, GoldGeneral, Rook, Bishop, SilverGeneral, Knight, Lance, Pawn,
    PromotedRook=Rook+PROMOTION_STEP, PromotedBishop, PromotedSilverGeneral,  PromotedKnight, PromotedLance, PromotedPawn,
};

enum Player{
    Sente=0, Gote
};

#endif // ENUMIRATIONS

