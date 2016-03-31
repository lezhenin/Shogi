#ifndef SHOGI_SAVE_H
#define SHOGI_SAVE_H

#include <vector>
#include <string>
#include "../Model/Piece.h"


struct Block
{

    Block(PieceType pieceType, Player player, int vertical, int horizontal) :
    pieceType(pieceType), player(player), vertical(vertical), horizontal(horizontal) { }

    PieceType pieceType;
    Player player;
    int vertical;
    int horizontal;
};

/**
 * @brief Класс сохранения
 */
class Save
{
public:

    Save() { }

    std::vector<Block> onBoard;
    std::vector<PieceType> senteCaptured;
    std::vector<PieceType> goteCaptured;

    //todo impl
    //std::string toString();
};


#endif //SHOGI_SAVE_H
