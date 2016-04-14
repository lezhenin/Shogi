#include "ShogiGameLogic.h"
#include "Exceptions/KingNotFoundException.h"
#include <algorithm>

//todo optimize all algorithms

//TODO: даже если не оптимизировать, предлагаю выделить отдельные методы, чекТо, чекЭто
bool ShogiGameLogic::checkMove(Piece *piece, Position destination) const
{
    std::vector<Direction> directions = table.getDirections(piece->getType(),piece->getPlayer());

    Position source = piece->getPosition();

    Direction *dir = findDirection(source, destination, directions);

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

std::vector<Position> ShogiGameLogic::getAllPositionToMove(Piece *piece) const
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

bool ShogiGameLogic::isUnderAttack(Player player, Position pos) const
{
    for (Piece *p: board->getPiecesOnBoard())
    {
        if ((p->getPlayer() == player) && checkMove(p, pos))
        {
            return true;
        }
    }
    return false;
}

bool ShogiGameLogic::checkShah(Player player) const
{
    Piece *king = findPiece(King, player, board->getPiecesOnBoard());
    if (king == nullptr)
    {
        throw KingNotFoundException();
    }
    player = changePlayer(player);
    return isUnderAttack(player, king->getPosition());
}

bool ShogiGameLogic::checkMate(Player player) const
{

    Piece *king = findPiece(King, player, board->getPiecesOnBoard());

    if (king == nullptr)
    {
        throw KingNotFoundException();
    }

    std::vector<Position> positions = getAllPositionToMove(king);
    positions.push_back(king->getPosition());

    player = changePlayer(player);

    for (Position &pos : positions)
    {
        if(board->getPiece(pos) != nullptr)
        {
            AbstractBoardMemento *memento = board->getMemento();
            board->removePiece(king->getPosition());
            board->removePiece(pos);
            board->setPiece(king, pos);
            bool kingIsUnderAttack = isUnderAttack(player, king->getPosition());
            board->setMemento(memento);
            delete memento;
            if(!kingIsUnderAttack)
            {
                return false;
            }
        }
        else
        {
            if (!isUnderAttack(player, pos))
            {
                return false;
            }
        }
    }
    return true;
}

//TODO: аналогичный метод есть Shogi.cpp, следует оставить только один из них
Player ShogiGameLogic::changePlayer(Player player) const
{
     return (player == Sente) ? Gote : Sente;
}

bool ShogiGameLogic::checkPromotion(Piece *piece) const
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

bool ShogiGameLogic::checkDrop(Piece *piece, Position pos)
{
    if (board->getPiece(pos) != nullptr)
    {
        return false;
    }
    //TODO: этот if выделить в метод
    if (piece->getType() == Pawn)
    {
        for (int i=1; i <= AbstractBoard::BOARD_HEIGHT; i++)
        {
            Position temp(i,pos.getVertical());
            if (board->getPiece(temp) != nullptr &&
                board->getPiece(temp) -> equals(piece))
            {
                return false;
            }
        }
    }

    //TODO: этот if выделить в метод
    if (piece->getType() == Pawn || piece->getType() == Lance)
    {
        if (piece->getPlayer() == Sente && pos.getHorizontal() == AbstractBoard::BOARD_HEIGHT
            || piece->getPlayer() == Gote && pos.getHorizontal() == 1)
        {
            return false;
        }
    }

    //TODO: этот if выделить в метод
    if(piece->getType()==Knight)
    {
        if (piece->getPlayer() == Sente && pos.getHorizontal() >= AbstractBoard::BOARD_HEIGHT - 1
           || piece->getPlayer() == Gote && pos.getHorizontal() <= 2)
        {
            return false;
        }
    }

    AbstractBoardMemento *memento = board->getMemento();
    board->setPiece(piece,pos);
    bool mate = checkMate(changePlayer(piece->getPlayer()));
    board->setMemento(memento);
    delete memento;
    return !mate;
}

Piece *ShogiGameLogic::findPiece(PieceType pieceType, Player player, ListOfPieces &pieces) const
{
    Piece samplePiece(pieceType,player);
    ListOfPieces::iterator iterator = std::find_if(pieces.begin(),pieces.end(),std::bind1st(std::mem_fun(&Piece::equals),&samplePiece));
    if (iterator != pieces.end())
    {
        return *iterator;
    }
    else
    {
        return nullptr;
    }
}

bool ShogiGameLogic::onBoard(Position position)  const
{
    return (position.getHorizontal() >= 1 && position.getHorizontal() <= AbstractBoard::BOARD_HEIGHT &&
            position.getVertical()   >= 1 && position.getVertical()   <= AbstractBoard::BOARD_WIDTH );
}

Direction *ShogiGameLogic::findDirection(Position &source, Position &destination, std::vector<Direction> &directions) const
{
    for (Direction &direction : directions)
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









