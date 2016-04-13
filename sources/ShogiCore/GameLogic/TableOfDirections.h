
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
//TODO: проверить, правильно ли я поняла, что было закодировано единичками
    const int UP    = -1;
    const int DOWN  = 1;
    const int RIGHT = 1;
    const int LEFT  = -1;
    std::map<PieceType,std::vector<Direction>> dirs= {
        //TODO: подобное форматирование позволит проверить по спецификации (правила игры), нет ли ошибки в заданных направлениях для каждой фигуры
        //Предлагаю всю таблицу привести к такому стилю
        {
            King, {Direction{     0, DOWN,  1},
                   Direction{ RIGHT, DOWN,  1},
                   Direction{ RIGHT,    0,  1},
                   Direction{ RIGHT,   UP,  1},
                   Direction{     0,   UP,  1},
                   Direction{  LEFT,   UP,  1},
                   Direction{  LEFT,    0,  1},
                   Direction{  LEFT, DOWN,  1}}
        },
        {Rook,{Direction{0,1}, Direction{1,0}, Direction{0,-1}, Direction{-1,0}}},
        {Bishop,{Direction{1,1}, Direction{1,-1}, Direction{-1,-1}, Direction{-1,1}}},
        {GoldGeneral, {Direction{0,1,1}, Direction{1,1,1}, Direction{1,0,1}, Direction{0,-1,1}, Direction{-1,0,1}, Direction{-1,1,1}}},
        {SilverGeneral, {Direction{1,1,1}, Direction{0,-1,1}, Direction{-1,0,1}, Direction{-1,1,1}}},
        {
            Knight, {Direction{RIGHT, DOWN * 3, 1},
                     Direction{ LEFT, DOWN * 3, 1}}
        },
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
