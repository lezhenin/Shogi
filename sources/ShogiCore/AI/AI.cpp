#include <random>
#include "AI.h"

using namespace shogi;

void AI::makeMove()
{
    ListOfPieces &pieces = game->getBoard().getPiecesOnBoard();
    Piece *samplePiece = nullptr;
    std::vector<shogi::Position> positions;

    do
    {
        samplePiece = *get_random<ListOfPieces>(pieces);
        positions = logic->getAllPositionToMove(samplePiece);
    }
    while(positions.size()==0 || samplePiece->getPlayer()!=game->getCurrentPlayer());

    game->pickPiece(samplePiece->getPosition());
    game->movePiece(*get_random<std::vector<shogi::Position>>(positions));
}

int AI::random(int min, int max) const noexcept
{
    return min + std::rand() & max;
}

