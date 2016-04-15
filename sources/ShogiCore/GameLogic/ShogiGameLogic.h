#ifndef SHOGI_SHOGIGAMELOGIC_H
#define SHOGI_SHOGIGAMELOGIC_H
#include "AbstractShogiGameLogic.h"
#include "TableOfDirections.h"

/**
 * @brief Реализация AbstractShogiGameLogic.
 */
class ShogiGameLogic: public AbstractShogiGameLogic
{
public:

    explicit ShogiGameLogic(AbstractBoard *board) : board(board){}

    bool checkMove(const Piece *piece, const Position &destination) const;
    bool checkShah(const Player &player) const;
    bool checkMate(const Player &player) const;
    bool checkPromotion(const Piece *piece) const;
    bool checkDrop(Piece *piece, const Position &position) const;

    virtual ~ShogiGameLogic() { }


private:

    bool isUnderAttack(const Player &player, const Position &position) const;
    bool onBoard(const Position &position) const;
    bool checkAbleToMove(const Piece *piece, const Position &position) const;

    std::vector<Position> getAllPositionToMove(const Piece *piece) const;

    const Direction *findDirection(const Position &source, const  Position &destination, const std::vector<Direction> &directions) const;

    AbstractBoard *board;
    TableOfDirections table;

};


#endif //SHOGI_SHOGIGAMELOGIC_H
