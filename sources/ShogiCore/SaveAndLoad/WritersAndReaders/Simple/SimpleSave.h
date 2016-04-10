#ifndef SHOGI_SAVE_H
#define SHOGI_SAVE_H

#include <vector>
#include <string>
#include "../../../Model/Piece.h"
#include "../Block.h"

/**
 * @brief Класс сохранения
 */
class SimpleSave
{
public:

    SimpleSave() { }

    std::vector<Block> onBoard;
    std::vector<PieceType> senteCaptured;
    std::vector<PieceType> goteCaptured;

};


#endif //SHOGI_SAVE_H
