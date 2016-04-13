#include "ShogiGameLogic.h"
#include "Exceptions/KingNotFoundException.h"
#include <algorithm>

//todo optimize all algorithms

//TODO: даже если не оптимизировать, предлагаю выделить отдельные методы, чекТо, чекЭто
// я заглянула в этот метод, чтобы понять, какие именно проверки проводятся, но поняла, что мне не судьба
// подозреваю, что в двух циклах осуществляются разные проверки
bool ShogiGameLogic::checkMove(Piece *piece, Position dest) const
{
    std::vector<Direction> dirs = table.getDirections(piece->getType());
    Position source = piece->getPosition();
    Direction *dir = nullptr;

    for(std::vector<Direction>::iterator it=dirs.begin(); it != dirs.end() && dir == nullptr; ++it)
    {
        if ((it->getX() * (dest.getHorizontal() - source.getHorizontal())
            - it->getY() * ((piece->getPlayer()==Sente) ? -1 : 1) * (dest.getVertical() - source.getVertical())) == 0
            && (pow(dest.getHorizontal() - source.getHorizontal(),2) + pow(dest.getVertical() - source.getVertical(),2))
               > (pow(dest.getHorizontal() - source.getHorizontal() - it->getY() * ((piece->getPlayer()==Sente) ? -1 : 1),2) + pow(dest.getVertical() - source.getVertical() - it->getX(),2)))
        {
            dir = &(*it);
        }
    }

    if(dir == nullptr) return false;

    for(int i = 1; i != dir->getLimit()+1; i++)
    {
        source = Position(source.getHorizontal() + dir->getY() * ((piece->getPlayer()==Sente) ? -1 : 1), source.getVertical() + dir->getX());
        if (source == dest && (board->getPiece(source) == nullptr || board->getPiece(source)->getPlayer() != piece->getPlayer())) return true;
        if (board->getPiece(source) != nullptr) return false;
    }
    return false;
}

std::vector<Position> ShogiGameLogic::getAllPositionToMove(Piece *piece) const
{
    //TODO: dirs -> directions
    std::vector<Direction> dirs = table.getDirections(piece->getType());
    Position source = piece->getPosition();
    std::vector<Position> positions;
    //TODO: кажется, что здесь возможен foreach синтаксис, или хотя бы слово auto
    //TODO: итератор не обязательно называть it, особенно если он участвует потом в нетривиальной логике, даже просто "d" (экономия буковок) было бы лучше
    for(std::vector<Direction>::iterator it = dirs.begin(); it != dirs.end(); ++it)
    {
        //TODO: предлагаю магическое условие на три строки вынести в отдельный метод, который вернет boolean, все ок или неок
        for(int i = 1; i != it->getLimit() + 1 &&
            //TODO: скобки помогают, их среда подсвечивает и они добавляют ясности по замыслу, и пробелы тоже помогают
                            (source.getVertical() + i * it->getX()) <= AbstractBoard::BOARD_WIDTH &&
                            (source.getVertical() + i * it->getX()) >= 1 &&
            //TODO: логику инвертирования координат для противников лучше вынести либо в Direction, либо в отдельный метод тут же
                            source.getHorizontal() + i * it->getY() * ((piece->getPlayer()==Sente) ? -1 : 1) <= AbstractBoard::BOARD_HEIGHT &&
                            source.getHorizontal() + i * it->getY() * ((piece->getPlayer()==Sente) ? -1 : 1) >= 1
                                                   ; ++i)
        {
            //TODO: tmp почти всегда плохое название. тут я выделила его и среда подсветила мне его в файле, и я попыталась оценить, насколько оно tmp, и что с ним делают
            //пусть его имя отвечает на вопрос зачем оно и что с ним делают
            Position tmp = Position(source.getHorizontal() + it->getY()*i * ((piece->getPlayer()==Sente) ? -1 : 1), source.getVertical() + it->getX()*i);
            if(board->getPiece(tmp) == nullptr || board->getPiece(tmp)->getPlayer() != piece->getPlayer())
            {
                positions.push_back(tmp);
            }
        }
    }
    return  positions;
}

bool ShogiGameLogic::isUnderAttack(Player player, Position pos) const {
    for (Piece *p: board->getPiecesOnBoard())
    {
        if ((p->getPlayer() == player) && checkMove(p, pos))
            return  true;
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
    player = transformPlayer(player);
    return isUnderAttack(player, king->getPosition());
}

bool ShogiGameLogic::checkMate(Player player) const {

    Piece *king = findPiece(King, player, board->getPiecesOnBoard());

    if (king == nullptr)
    {
        throw KingNotFoundException();
    }

    std::vector<Position> positions = getAllPositionToMove(king);
    positions.push_back(king->getPosition());

    player = transformPlayer(player);

    for (Position pos : positions)
    {
        if(board->getPiece(pos) != nullptr)
        {
            AbstractBoardMemento *abm = board->getMemento();
            board->removePiece(king->getPosition());
            board->removePiece(pos);
            board->setPiece(king,pos);
            bool kingIsUnderAttack = isUnderAttack(player,king->getPosition());
            board->setMemento(abm);
            delete abm;
            if(!kingIsUnderAttack)
            {
                return false;
            }

        }
        else
        {
            if (!isUnderAttack(player, pos))
                return false;
        }
    }
    return true;
}

//TODO: аналогичный метод есть Shogi.cpp, следует оставить только один из них
Player ShogiGameLogic::transformPlayer(Player pl) const {
     return (Player)((int)(pl+1)%2);
}

bool ShogiGameLogic::checkPromotion(Piece *piece) const {
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

    AbstractBoardMemento *abm = board->getMemento();
    board->setPiece(piece,pos);
    Player player = transformPlayer(piece->getPlayer());
    bool mate = checkMate(player);
    board->setMemento(abm);
    delete abm;
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





