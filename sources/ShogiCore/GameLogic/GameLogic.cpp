#include "GameLogic.h"
#include "Exceptions/KingNotFoundException.h"
#include <algorithm>

using namespace shogi;

bool GameLogic::checkMove(const Piece *piece, const Position &destination) const noexcept
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

std::vector<Position> GameLogic::getAllPositionToMove(const Piece *piece) const noexcept
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

bool GameLogic::isUnderAttack(const Player &player, const Position &position) const noexcept
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

bool GameLogic::checkShah(const Player &player) const
{
    Piece *king = board->findPiece(King, player, board->getPiecesOnBoard());
    if (king == nullptr)
    {
        throw KingNotFoundException();
    }
    return isUnderAttack(player.nextPlayer(), king->getPosition());
}

bool GameLogic::checkMate(const Player &player) const
{

    Piece *king = board->findPiece(King, player, board->getPiecesOnBoard());

    if (king == nullptr)
    {
        throw KingNotFoundException();
    }

    std::vector<Position> positions = getAllPositionToMove(king);
    positions.push_back(king->getPosition());

    const Player nextPlayer = player.nextPlayer();

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

bool GameLogic::checkPromotion(const Piece *piece) const noexcept
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

bool GameLogic::checkDrop(Piece *piece, const Position &position) const noexcept
{
    if (board->getPiece(position) != nullptr)
    {
        return false;
    }

    if (piece->getType() == Pawn)
    {
        if(!checkLine(piece, position.getVertical()))
        {
            return false;
        }
    }

    if(!checkAbleToMove(piece, position))
    {
        return false;
    }

    AbstractBoardMemento *memento = board->getMemento();
    board->setPiece(piece,position);
    bool mate = checkMate(piece->getPlayer().nextPlayer());
    board->setMemento(memento);
    delete memento;
    return !mate;
}

bool GameLogic::onBoard(const Position &position)  const noexcept
{
    return (position.getHorizontal() >= 1 && position.getHorizontal() <= AbstractBoard::BOARD_HEIGHT &&
            position.getVertical()   >= 1 && position.getVertical()   <= AbstractBoard::BOARD_WIDTH );
}

const Direction *GameLogic::findDirection(const Position &source, const Position &destination, const std::vector<Direction> &directions) const noexcept
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

bool GameLogic::checkAbleToMove(const Piece *piece, const Position &position) const noexcept
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

bool GameLogic::checkLine(const Piece *pawn, int vertical) const noexcept
{
    Piece samplePiece(pawn->getType(), pawn->getPlayer());
    for (int i=1; i <= AbstractBoard::BOARD_HEIGHT; i++)
    {
        Position temp(i, vertical);
        if (board->getPiece(temp) != nullptr &&
            board->getPiece(temp) -> equals(&samplePiece))
        {
            return false;
        }
    }
    return true;
}













