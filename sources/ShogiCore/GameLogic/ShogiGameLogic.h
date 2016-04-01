#ifndef SHOGI_SHOGIGAMELOGIC_H
#define SHOGI_SHOGIGAMELOGIC_H
#include "AbstractShogiGameLogic.h"
#include "TableOfDirections.h"

/*
 * @brief Реализация AbstractShogiGameLogic.
 */
class ShogiGameLogic: public AbstractShogiGameLogic
{
public:

    explicit ShogiGameLogic(AbstractBoard *board) : board(board){}
    bool checkMove(Piece *piece, Position pos) const;
    bool checkShah(Player player) const;
    bool checkMate(Player player) const;
    bool checkPromotion(Piece *piece) const;
    bool checkDrop(Piece *piece, Position pos);


private:
    Player transformPlayer(Player pl) const;
    bool isUnderAttack(Player player, Position pos) const;
    std::vector<Position> getAllPositionToMove(Piece *piece) const;
    AbstractBoard *board;
    TableOfDirections table;

};


#endif //SHOGI_SHOGIGAMELOGIC_H
