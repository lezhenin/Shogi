#include "BoardMemento.h"

BoardMemento::BoardMemento(Board *board): board(board)
{
    this->capturedPieces[Sente] = board->getCapturedPieces(Sente);
    this->capturedPieces[Gote] = board->getCapturedPieces(Gote);
    for(ListOfPieces::iterator it = board->getPiecesOnBoard().begin(); it != board->getPiecesOnBoard().end(); ++it)
    {
        Pair p;
        p.piece=*it;
        p.square=(*it)->getSquare();
        pairs.push_back(p);
    }
}

void BoardMemento::restore()
{
    for(ListOfPieces::iterator it = this->board->getPiecesOnBoard().begin(); it != this->board->getPiecesOnBoard().end(); ++it)
    {
        Piece *p =this->board->getPiece((*it)->getPosition());
        p->getSquare()->setPiece(nullptr);
        p->setSquare(nullptr);
    }
    this->board->getPiecesOnBoard().clear();
    for(std::vector<Pair>::iterator it = this->pairs.begin(); it < this->pairs.end(); ++it)
    {
        this->board->setPiece(it->piece,it->square->getPosition());
    }

    board->getCapturedPieces(Sente).clear();
    board->getCapturedPieces(Gote).clear();
    board->getCapturedPieces(Sente) = capturedPieces.at(Sente);
    board->getCapturedPieces(Gote) = capturedPieces.at(Gote);
}


