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

    bool checkMove(Piece *piece, Position destination) const;
    bool checkShah(Player player) const;
    bool checkMate(Player player) const;
    bool checkPromotion(Piece *piece) const;
    bool checkDrop(Piece *piece, Position pos);

    virtual ~ShogiGameLogic() { }


private:
    Player transformPlayer(Player pl) const;

    bool isUnderAttack(Player player, Position pos) const;
    bool onBoard(Position position) const;

    std::vector<Position> getAllPositionToMove(Piece *piece) const;

    Piece* findPiece(PieceType pieceType, Player player, ListOfPieces& pieces) const;

    Direction *findDirection(Position &source, Position &destination, std::vector<Direction> &directions) const;

    AbstractBoard *board;
    TableOfDirections table;

};


#endif //SHOGI_SHOGIGAMELOGIC_H
