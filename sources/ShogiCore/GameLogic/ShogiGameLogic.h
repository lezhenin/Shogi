#ifndef SHOGI_SHOGIGAMELOGIC_H
#define SHOGI_SHOGIGAMELOGIC_H
#include "AbstractShogiGameLogic.h"

using TableOfDirections = std::map<PieceType,std::vector<Direction>>;

class ShogiGameLogic: public AbstractShogiGameLogic {
public:

    explicit ShogiGameLogic(AbstractBoard &board) : board(board) { }

    bool checkMove(Piece *piece, Position pos) const;
    bool checkShah(Player player) const;
    bool checkMate(Player player) const;
    bool checkPromotion(Piece *piece) const;
    bool checkDrop(Piece *piece, Position pos);


private:
    Player transformPlayer(Player pl) const;
    bool isUnderAttack(Player player, Position pos) const;
    std::vector<Position> getAllPosition(Piece *piece) const;

    AbstractBoard &board;
    TableOfDirections table =
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
