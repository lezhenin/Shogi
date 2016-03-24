#include "ShogiGameLogic.h"

//todo optimize algorithm
bool ShogiGameLogic::checkMove(Piece *piece, Position dest) const
{
    std::vector<Direction> dirs = directions.at(piece->getType());
    Position source = piece->getPosition();
    Direction *dir = nullptr;

    for(std::vector<Direction>::iterator it=dirs.begin(); it != dirs.end(); ++it)
    {
        if ((it->getX() * (dest.getHorizontal() - source.getHorizontal())
            - it->getY() * (dest.getVertical() - source.getVertical())) == 0)
        {
            dir = &(*it);
            break;
        }
    }

    if(dir == nullptr) return false;

    for(int i = 1; i != dir->getLimit()+1; i++)
    {
        source = Position(source.getHorizontal() + dir->getY(), source.getVertical() + dir->getX());
        if (source == dest) return true;
        if (board.getPiece(source) != nullptr) break;
    }
    return false;

}

