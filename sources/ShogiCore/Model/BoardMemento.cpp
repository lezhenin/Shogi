#include "BoardMemento.h"
//todo for each loops
BoardMemento::BoardMemento(Board *board): board(board)
{
    this->capturedPieces[Sente] = board->getCapturedPieces(Sente);
    this->capturedPieces[Gote] = board->getCapturedPieces(Gote);
    for(ListOfPieces::iterator it = board->getPiecesOnBoard().begin(); it != board->getPiecesOnBoard().end(); ++it)
    {
        PieceInfo p;
        p.piece=*it;
        p.square=(*it)->getSquare();
        p.promote=(*it)->wasPromoted();
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
    for(std::vector<PieceInfo>::iterator it = this->pairs.begin(); it < this->pairs.end(); ++it)
    {
        this->board->setPiece(it->piece,it->square->getPosition());
        if(it->promote)
        {
            it->piece->promote();
        }
        else
        {
            it->piece->unPromote();
        }
    }

    board->getCapturedPieces(Sente).clear();
    board->getCapturedPieces(Gote).clear();
    board->getCapturedPieces(Sente) = capturedPieces.at(Sente);
    board->getCapturedPieces(Gote) = capturedPieces.at(Gote);
}


