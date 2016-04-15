#ifndef SHOGI_BLOCK_H
#define SHOGI_BLOCK_H


#include "../Model/Piece.h"
/**
 * @brief Класс хранит информацию о фигуре.
 *
 * Класс учавствует при сохранении и загрузки игры.
 */
class Block
{
public:
    Block(const PieceType pieceType, const Player &player, const Position &position) : pieceType(pieceType), player(player),
                                                                          position(position) { }

    PieceType pieceType;
    Player player;
    Position position;
};


#endif //SHOGI_BLOCK_H
