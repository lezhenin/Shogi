
#ifndef SHOGI_TABLEOFDIRECTIONS_H
#define SHOGI_TABLEOFDIRECTIONS_H
#include <vector>
#include <map>
#include "Direction.h"
#include "../Model/Piece.h"

/**
 * @brief Класс содержащий таблицу фигур и их возможных направлений ходов.
 */
class TableOfDirections
{
public:

    std::vector<Direction> getDirections(PieceType pieceType, Player player = Gote) const
    {
        if (player == Gote)
        {
            return directions.at(pieceType);
        }

        std::vector<Direction> newDirections;
        for (Direction direction: directions.at(pieceType))
        {
            Direction newDirection(direction.getX(),direction.getY() * (-1));
            newDirections.push_back(newDirection);
        }
        return newDirections;
    }

private:

    std::map<PieceType, std::vector<Direction>> directions= {
            {
                    King,           {Direction{     0,   UP, 1},
                                     Direction{ RIGHT,   UP, 1},
                                     Direction{ RIGHT,    0, 1},
                                     Direction{ RIGHT, DOWN, 1},
                                     Direction{     0, DOWN, 1},
                                     Direction{  LEFT, DOWN, 1},
                                     Direction{  LEFT,    0, 1},
                                     Direction{  LEFT,   UP, 1}}
            },
            {       Rook,           {Direction{     0,   UP},
                                     Direction{ RIGHT,    0},
                                     Direction{     0, DOWN},
                                     Direction{  LEFT,    0}}
            },
            {       Bishop,         {Direction{ RIGHT,   UP},
                                     Direction{ RIGHT, DOWN},
                                     Direction{  LEFT,   UP},
                                     Direction{  LEFT, DOWN}}
            },
            {       GoldGeneral,    {Direction{     0,   UP, 1},
                                     Direction{     0, DOWN, 1},
                                     Direction{ RIGHT,   UP, 1},
                                     Direction{ RIGHT,    0, 1},
                                     Direction{  LEFT,    0, 1},
                                     Direction{  LEFT,   UP, 1}}
            },
            {       SilverGeneral,  {Direction{ RIGHT,   UP, 1},
                                     Direction{  LEFT,   UP, 1},
                                     Direction{     0,   UP, 1},
                                     Direction{ RIGHT, DOWN, 1},
                                     Direction{  LEFT, DOWN, 1}}
            },
            {
                    Knight,         {Direction{ RIGHT, UP * 3, 1},
                                     Direction{  LEFT, UP * 3, 1}}
            },
            {       Lance,          {Direction{ 0, UP}}
            },
            {       Pawn,           {Direction{ 0, UP, 1}}
            },
            {       PromotedRook,   {Direction{     0,   UP},
                                     Direction{ RIGHT,    0},
                                     Direction{     0, DOWN},
                                     Direction{  LEFT,    0},
                                     Direction{ RIGHT,   UP, 1},
                                     Direction{ RIGHT, DOWN, 1},
                                     Direction{  LEFT, DOWN, 1},
                                     Direction{  LEFT, UP,   1}}
            },
            {       PromotedBishop, {Direction{ RIGHT,   UP},
                                     Direction{ RIGHT, DOWN},
                                     Direction{  LEFT,   UP},
                                     Direction{  LEFT, DOWN},
                                     Direction{     0,   UP, 1},
                                     Direction{     0, DOWN, 1},
                                     Direction{ RIGHT,    0, 1},
                                     Direction{  LEFT,    0, 1}}
            },
            {       PromotedLance,  {Direction{     0,   UP, 1},
                                     Direction{     0, DOWN, 1},
                                     Direction{ RIGHT,   UP, 1},
                                     Direction{ RIGHT,    0, 1},
                                     Direction{  LEFT,    0, 1},
                                     Direction{  LEFT,   UP, 1}}
            },
            {       PromotedPawn,   {Direction{     0,   UP, 1},
                                     Direction{     0, DOWN, 1},
                                     Direction{ RIGHT,   UP, 1},
                                     Direction{ RIGHT,    0, 1},
                                     Direction{  LEFT,    0, 1},
                                     Direction{  LEFT,   UP, 1}}
            },
            {       PromotedKnight, {Direction{     0,   UP, 1},
                                     Direction{     0, DOWN, 1},
                                     Direction{ RIGHT,   UP, 1},
                                     Direction{ RIGHT,    0, 1},
                                     Direction{  LEFT,    0, 1},
                                     Direction{  LEFT,   UP, 1}}
            }
    };
    };


#endif //SHOGI_TABLEOFDIRECTIONS_H
