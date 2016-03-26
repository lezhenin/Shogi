#include "ShogiGameLogic.h"
#include <algorithm>

//todo optimize algorithms
bool ShogiGameLogic::checkMove(Piece *piece, Position dest) const
{
    std::vector<Direction> dirs = table.at(piece->getType());
    Position source = piece->getPosition();
    Direction *dir = nullptr;

    for(std::vector<Direction>::iterator it=dirs.begin(); it != dirs.end(); ++it)
    {
        if ((it->getX() * (dest.getHorizontal() - source.getHorizontal())
            - it->getY() * (dest.getVertical() - source.getVertical())) == 0
            && (pow(dest.getHorizontal() - source.getHorizontal(),2) + pow(dest.getVertical() - source.getVertical(),2))
               > (pow(dest.getHorizontal() - source.getHorizontal() - it->getY(),2) + pow(dest.getVertical() - source.getVertical() - it->getX(),2)))
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
    for(std::vector<Direction>::iterator it = dirs.begin(); it != dirs.end(); ++it)
    {
        for(int i = 1; i!=it->getLimit()+1 && source.getVertical() + i * it->getX() <= AbstractBoard::BOARD_WIDTH && source.getVertical() + i * it->getX() >= 1
                       && source.getHorizontal() + i * it->getY() <= AbstractBoard::BOARD_HEIGHT && source.getHorizontal() + i * it->getY() >= 1; ++i)
        {
            Position tmp = Position(source.getHorizontal() + it->getY()*i, source.getVertical() + it->getX()*i);
            if(board.getPiece(tmp) == nullptr || board.getPiece(tmp)->getPlayer() != piece->getPlayer())
            {
                positions.push_back(tmp);
            }
        }
    }
    return  positions;
}

bool ShogiGameLogic::isUnderAttack(Player player, Position pos) const {
    for (Piece *p: board.getPiecesOnBoard())
    {
        if (p->getPlayer() == player && checkMove(p, pos)) return  true;
    }
    return false;
}



bool ShogiGameLogic::checkShah(Player player) const
{
    Piece tmp(King, player);
    Piece *king = nullptr;
    for (ListOfPieces::iterator it = board.getPiecesOnBoard().begin(); king == nullptr && it != board.getPiecesOnBoard().end(); ++it) {
        if (tmp.equals(*it)) {
            king = *it;
        }

    }
    //todo throw exception if king == nullptr
    player = transformPlayer(player);
    return isUnderAttack(player,king->getPosition());
}

bool ShogiGameLogic::checkMate(Player player) const {
    Piece tmp(King, player);
    Piece *king = nullptr;
    for (ListOfPieces::iterator it = board.getPiecesOnBoard().begin(); king == nullptr && it != board.getPiecesOnBoard().end(); ++it) {
        if (tmp.equals(*it)) {
            king = *it;
        }
    }
    std::vector<Position> positions = getAllPosition(king);
    positions.push_back(king->getPosition());

    player = transformPlayer(player);

    for (Position pos : positions)
    {
        if(board.getPiece(pos)==0)
        {
            if (!isUnderAttack(player, pos)) return false;
        }
        else
        {
            AbstractBoardMemento *abm = board.getMemento();
            board.removePiece(king->getPosition());
            board.removePiece(pos);
            board.setPiece(king,pos);
            if(isUnderAttack(player,king->getPosition()))
            {
                board.setMemento(abm);
            }
            else
            {
                board.setMemento(abm);
                return false;
            }
        }
    }
    return true;
}

Player ShogiGameLogic::transformPlayer(Player pl) const {
     return (Player)((int)(pl+1)%2);
}

bool ShogiGameLogic::checkPromotion(Piece *piece) const {
    if(piece->getPlayer()==Sente)
    {
        return piece->canBePromoted() && piece->getPosition().getHorizontal()<=3;
    }
    else
    {
        return piece->canBePromoted() && piece->getPosition().getHorizontal()>=7;
    }
}

bool ShogiGameLogic::checkDrop(Piece *piece, Position pos)
{
    if (board.getPiece(pos) != nullptr) return false;
    if (piece->getType() == Pawn)
    {
        for (int i=1; i <= AbstractBoard::BOARD_HEIGHT; i++)
        {
            if (board.getPiece(Position(i,pos.getVertical()))->equals(piece))
            {
                return false;
            }
        }
    }
    AbstractBoardMemento *abm = board.getMemento();
    board.setPiece(piece,pos);
    std::vector<Position> vec = getAllPosition(piece);

    if(vec.empty())
    {
        board.setMemento(abm);
        return false;
    }

    Player player = transformPlayer(piece->getPlayer());
    if (checkMate(player))
    {
        board.setMemento(abm);
        return false;
    }
    board.setMemento(abm);
    return true;
}























