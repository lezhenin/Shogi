
#ifndef SHOGI_TABLEOFDIRECTIONS_H
#define SHOGI_TABLEOFDIRECTIONS_H
#include <vector>
#include <map>
#include "Direction.h"
#include "../Model/Piece.h"
/**
 * Класс содержащий таблицу фигур и их возможных направлений ходов.
 */
class TableOfDirections
{
public:
    std::vector<Direction> getDirections(PieceType pieceType) const{ return dirs.at(pieceType);}

private:
    std::map<PieceType,std::vector<Direction>> dirs= {
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


#endif //SHOGI_TABLEOFDIRECTIONS_H
