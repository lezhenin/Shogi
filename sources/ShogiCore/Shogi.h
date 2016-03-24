#ifndef SHOGI_H
#define SHOGI_H
#include "ShogiGameAPI.h"

class Shogi: ShogiGameAPI
{
public:

    Shogi(){};

    void initGame();
    void pickPiece(const Position& position);
    void movePiece(const Position& position);
    void promotePiece(const Position& position);
    void dropPiece(const PieceType pt, const Position& position);

    Board &getBoard();
    std::vector<GameSituation> getGameSituation();

    ~Shogi();

private:
    Piece* pickedPiece = nullptr;
    Board board{Board::BOARD_HEIGHT,Board::BOARD_WIDTH};
};

#endif // SHOGI_H
