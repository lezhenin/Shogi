#include "Shogi.h"
#include "GameSituations/Shah.h"
#include "GameSituations/Mate.h"
#include "GameSituations/PromotionIsAvailable.h"
#include <algorithm>



void Shogi::initGame()
{
    Piece *p = new Piece(Rook,Sente,0);
    this->board.setPiece(p,Position(5,3));
}

void Shogi::pickPiece(const Position &position)
{
    Piece* p = this->board.getPiece(position);
    if(p!=nullptr)
    {
        this->pickedPiece = p;
    }
}

void Shogi::movePiece(const Position &position)
{
    if(pickedPiece != nullptr)
    {
        this->board.removePiece(pickedPiece->getPosition());
        this->board.setPiece(pickedPiece,position);

    }
    pickedPiece = nullptr;
}

void Shogi::promotePiece(const Position &position)
{
    this->board.getPiece(position)->promote();
}

void Shogi::dropPiece(const PieceType pt, const Position &position)
{
    Piece  *p = new Piece(pt,Sente);
    this->getBoard().getSenteCapturedPieces().push_back(p);

    ListOfPieces * cap = &this->getBoard().getSenteCapturedPieces();
    for(ListOfPieces::iterator it = cap->begin(); it != cap->end(); ++it)
    {
        if((*it)==p)
        {
            this->board.setPiece((*it),position);
        }
    }
    cap->remove(p);

}

Board &Shogi::getBoard()
{
    return this->board;
}

ListOfGameSituations Shogi::getGameSituation()
{
    ListOfGameSituations list;
    std::shared_ptr<GameSituation> p1(new Shah());
    std::shared_ptr<GameSituation> p2(new Mate());
    std::shared_ptr<GameSituation> p3(new PromotionIsAvailable());
    list.push_back(p1);
    list.push_back(p2);
    list.push_back(p3);
    return list;

}

Shogi::~Shogi()
{
    for(Piece *piece: this->board.getPiecesOnBoard()){
        delete piece;
    }
}

