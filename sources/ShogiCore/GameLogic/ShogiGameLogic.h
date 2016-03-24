#ifndef SHOGI_SHOGIGAMELOGIC_H
#define SHOGI_SHOGIGAMELOGIC_H
#include <map>
#include <vector>
#include "../Model/Piece.h"
#include "Direction.h"

class ShogiGameLogic {
public:

private:
 std::map<PieceType,std::vector<Direction>> directions =
         {
                 {King,{Direction{0,1,1}, Direction{1,1,1}, Direction{1,0,1}, Direction{1,-1,1}, Direction{0,-1,1}, Direction{-1,-1,1}, Direction{-1,0,1}, Direction{-1,1,1}}},
                 {Rook,{Direction{0,1}, Direction{1,0}, Direction{0,-1}, Direction{-1,0}}},
                 {Bishop,{Direction{1,1}, Direction{1,-1}, Direction{-1,-1}, Direction{-1,1}}},
                 {GoldGeneral, {Direction{0,1,1}, Direction{1,1,1}, Direction{1,0,1}, Direction{0,-1,1}, Direction{-1,0,1}, Direction{-1,1,1}}},
                 {SilverGeneral, {Direction{1,1,1}, Direction{0,-1,1}, Direction{-1,0,1}, Direction{-1,1,1}}},
                 {Knight, {Direction{1,3,1},Direction{-1,3,1}}},
                 {Lance, {Direction{0,1}}},
                 {Pawn, {Direction{0,1,1}}},
                 {PromotedRook, {Direction{0,1}, Direction{1,1,1}, Direction{1,0}, Direction{1,-1,1}, Direction{0,-1}, Direction{-1,-1,1}, Direction{-1,0}, Direction{-1,1,1}}},
                 {PromotedBishop, {Direction{0,1,1}, Direction{1,1}, Direction{1,0,1}, Direction{1,-1}, Direction{0,-1,1}, Direction{-1,-1}, Direction{-1,0,1}, Direction{-1,1}}},
                 {PromotedLance, {Direction{0,1,1}, Direction{1,1,1}, Direction{1,0,1}, Direction{0,-1,1}, Direction{-1,0,1}, Direction{-1,1,1}}},
                 {PromotedPawn, {Direction{0,1,1}, Direction{1,1,1}, Direction{1,0,1}, Direction{0,-1,1}, Direction{-1,0,1}, Direction{-1,1,1}}},
                 {PromotedKnight, {Direction{0,1,1}, Direction{1,1,1}, Direction{1,0,1}, Direction{0,-1,1}, Direction{-1,0,1}, Direction{-1,1,1}}}
         };
};


#endif //SHOGI_SHOGIGAMELOGIC_H
