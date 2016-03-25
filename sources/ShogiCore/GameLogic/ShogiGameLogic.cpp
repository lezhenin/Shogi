#include "ShogiGameLogic.h"
#include <algorithm>
#include <functional>
//todo optimize algorithm
bool ShogiGameLogic::checkMove(Piece *piece, Position dest) const
{
    std::vector<Direction> dirs = table.at(piece->getType());
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
        if (source == dest && (board.getPiece(source) == nullptr || board.getPiece(source)->getPlayer() != piece->getPlayer())) return true;
        if (board.getPiece(source) != nullptr) return false;
    }


}

std::vector<Position> ShogiGameLogic::getAllPosition(Piece *piece) const
{
    std::vector<Direction> dirs = table.at(piece->getType());
    Position source = piece->getPosition();
    std::vector<Position> positions;
    for(std::vector<Direction>::iterator it=dirs.begin(); it != dirs.end(); ++it)
    {
        for(int i = 1; i!=it->getLimit() && source.getVertical() + i <= AbstractBoard::BOARD_WIDTH
                       && source.getVertical() + i < AbstractBoard::BOARD_HEIGHT; ++i)
        {
            positions.push_back(Position(source.getHorizontal() + it->getY()*i, source.getVertical() + it->getX()*i));
        }
    }
    return  positions;
}



bool ShogiGameLogic::checkShah(Player player)
{
    Piece tmp(King, player);
    Piece *king = nullptr;
    for (ListOfPieces::iterator it = board.getPiecesOnBoard().begin(); king == nullptr && it != board.getPiecesOnBoard().end(); ++it) {
        if (tmp.equals(*it)) {
            king = *it;
        }

    }
    //todo throw exception if king == nullptr
    for (Piece *p: board.getPiecesOnBoard())
    {
        if (p->getPlayer()!=player && checkMove(p,king->getPosition())) return  true;
    }
    return false;
}

bool ShogiGameLogic::checkMate() {
    return false;
}















