#include "ShogiGameLogic.h"
#include "Exceptions/KingNotFoundException.h"
#include <algorithm>

//TODO: даже если не оптимизировать, предлагаю выделить отдельные методы, чекТо, чекЭто
bool ShogiGameLogic::checkMove(const Piece *piece, const Position &destination) const
{
    std::vector<Direction> directions = table.getDirections(piece->getType(),piece->getPlayer());

    Position source = piece->getPosition();

    const Direction *dir = findDirection(source, destination, directions);

    if(dir == nullptr)
    {
        return false;
    }

    for(int i = 1; i != dir->getLimit()+1; i++)
    {
        source = Position(source.getHorizontal() + dir->getY(), source.getVertical() + dir->getX());

        if (source == destination &&
           (board->getPiece(source) == nullptr ||
            board->getPiece(source)->getPlayer() != piece->getPlayer()))
        {
            return true;
        }
        if (board->getPiece(source) != nullptr)
        {
            return false;
        }
    }
    return false;
}

std::vector<Position> ShogiGameLogic::getAllPositionToMove(const Piece *piece) const
{
    std::vector<Direction> directions = table.getDirections(piece->getType(),piece->getPlayer());
    Position source = piece->getPosition();
    std::vector<Position> positions;

    for (Direction &direction : directions)
    {
        for(int i = 1; i != direction.getLimit() + 1; ++i)
        {
            Position destination = Position(source.getHorizontal() + direction.getY() * i,
                                            source.getVertical()   + direction.getX() * i);
            if(!onBoard(destination))
            {
                break;
            }
            if (board->getPiece(destination) == nullptr ||
                board->getPiece(destination)->getPlayer() != piece->getPlayer())
            {
                positions.push_back(destination);
            }
        }
    }
    return  positions;
}

bool ShogiGameLogic::isUnderAttack(const Player player, const Position &position) const
{
    for (Piece *p: board->getPiecesOnBoard())
    {
        if ((p->getPlayer() == player) && checkMove(p, position))
        {
            return true;
        }
    }
    return false;
}

bool ShogiGameLogic::checkShah(const Player player) const
{
    Piece *king = board->findPiece(King, player, board->getPiecesOnBoard());
    if (king == nullptr)
    {
        throw KingNotFoundException();
    }
    return isUnderAttack(changePlayer(player), king->getPosition());
}

bool ShogiGameLogic::checkMate(const Player player) const
{

    Piece *king = board->findPiece(King, player, board->getPiecesOnBoard());

    if (king == nullptr)
    {
        throw KingNotFoundException();
    }

    std::vector<Position> positions = getAllPositionToMove(king);
    positions.push_back(king->getPosition());

    const Player nextPlayer = changePlayer(player);

    for (Position &pos : positions)
    {
        if(board->getPiece(pos) != nullptr)
        {
            AbstractBoardMemento *memento = board->getMemento();
            board->removePiece(king->getPosition());
            board->removePiece(pos);
            board->setPiece(king, pos);
            bool kingIsUnderAttack = isUnderAttack(nextPlayer, king->getPosition());
            board->setMemento(memento);
            delete memento;
            if(!kingIsUnderAttack)
            {
                return false;
            }
        }
        else
        {
            if (!isUnderAttack(nextPlayer, pos))
            {
                return false;
            }
        }
    }
    return true;
}

//TODO: аналогичный метод есть Shogi.cpp, следует оставить только один из них
Player ShogiGameLogic::changePlayer(const Player player) const
{
     return (player == Sente) ? Gote : Sente;
}

bool ShogiGameLogic::checkPromotion(const Piece *piece) const
{
    if(piece->wasPromoted() || !piece->canBePromoted())
    {
        return false;
    }
    if(piece->getPlayer() == Sente)
    {
        return  piece->getPosition().getHorizontal() <= AbstractBoard::PROMOTION_LINE_SENTE;
    }
    else
    {
        return  piece->getPosition().getHorizontal() >= AbstractBoard::PROMOTION_LINE_GOTE;
    }
}

bool ShogiGameLogic::checkDrop(Piece *piece, const Position &position) const
{
    if (board->getPiece(position) != nullptr)
    {
        return false;
    }
    //TODO: этот if выделить в метод
    if (piece->getType() == Pawn)
    {
        for (int i=1; i <= AbstractBoard::BOARD_HEIGHT; i++)
        {
            Position temp(i,position.getVertical());
            if (board->getPiece(temp) != nullptr &&
                board->getPiece(temp) -> equals(piece))
            {
                return false;
            }
        }
    }
    
    if(!checkAbleToMove(piece, position))
    {
        return false;
    }

    AbstractBoardMemento *memento = board->getMemento();
    board->setPiece(piece,position);
    bool mate = checkMate(changePlayer(piece->getPlayer()));
    board->setMemento(memento);
    delete memento;
    return !mate;
}

bool ShogiGameLogic::onBoard(const Position &position)  const
{
    return (position.getHorizontal() >= 1 && position.getHorizontal() <= AbstractBoard::BOARD_HEIGHT &&
            position.getVertical()   >= 1 && position.getVertical()   <= AbstractBoard::BOARD_WIDTH );
}

const Direction *ShogiGameLogic::findDirection(const Position &source, const Position &destination, const std::vector<Direction> &directions) const
{
    for (const Direction &direction : directions)
    {
        if ((direction.getX() * (destination.getHorizontal() - source.getHorizontal()) -
             direction.getY() * (destination.getVertical()   - source.getVertical())) == 0

            && (pow(destination.getHorizontal() - source.getHorizontal(), 2) +
                pow(destination.getVertical()   - source.getVertical(), 2)) >
               (pow(destination.getHorizontal() - source.getHorizontal() - direction.getY(), 2) +
                pow(destination.getVertical()   - source.getVertical()   - direction.getX(), 2)))
        {
            return &direction;
        }
    }
    return nullptr;
}

bool ShogiGameLogic::checkAbleToMove(const Piece *piece, const Position &position) const
{

    if (piece->getType() == Pawn || piece->getType() == Lance)
    {
        if (piece->getPlayer() == Sente && position.getHorizontal() == AbstractBoard::BOARD_HEIGHT
            || piece->getPlayer() == Gote && position.getHorizontal() == 1)
        {
            return false;
        }
    }

    if(piece->getType()==Knight)
    {
        if (piece->getPlayer() == Sente && position.getHorizontal() >= AbstractBoard::BOARD_HEIGHT - 1
            || piece->getPlayer() == Gote && position.getHorizontal() <= 2)
        {
            return false;
        }
    }

    return true;
}











