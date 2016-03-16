#include "BoardMemento.h"

BoardMemento::BoardMemento(BoardInterface &board): board(board)
{
    for(Pieces::iterator it = board.getSenteCapturedPieces().begin(); it != board.getSenteCapturedPieces().end(); ++it)
    {
        this->senteCaptured.push_back(*it);
    }
    for(Pieces::iterator it = board.getGoteCapturedPieces().begin(); it != board.getGoteCapturedPieces().end(); ++it)
    {
        this->goteCaptured.push_back(*it);
    }
    for(Pieces::iterator it = board.getPiecesOnBoard().begin(); it != board.getPiecesOnBoard().end(); ++it)
    {
        Pair p;
        p.piece=*it;
        p.square=(*it)->getSquare();
        pairs.push_back(p);
    }
}

void BoardMemento::restore()
{
    for(Pieces::iterator it = board.getPiecesOnBoard().begin(); it != board.getPiecesOnBoard().end(); ++it)
    {
        board.removePiece((*it)->getPosition());
    }
    for(std::vector<Pair>::iterator it = this->pairs.begin(); it < this->pairs.end(); ++it)
    {
        board.setPiece(it->piece,it->square->getPosition());
        board.getPiecesOnBoard().push_back(it->piece);
    }
    for(Pieces::iterator it = this->senteCaptured.begin(); it != this->senteCaptured.end(); ++it)
    {
        board.getSenteCapturedPieces().push_back(*it);
    }
    for(Pieces::iterator it = this->goteCaptured.begin(); it != this->goteCaptured.end(); ++it)
    {
        board.getGoteCapturedPieces().push_back(*it);
    }
}

BoardMemento::~BoardMemento() {

}
