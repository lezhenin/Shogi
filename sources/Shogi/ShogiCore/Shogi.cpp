#include "Shogi.h"

Shogi::Shogi()
{
    this->board = new Board(BOARD_WIDTH, BOARD_HEIGHT);
}

void Shogi::initGame()
{
    Piece *p = new Piece(Rook,Sente,0);
    this->board->setPiece(p,Position(5,3));
}

void Shogi::pickPiece(Position &position)
{

}

void Shogi::movePiece(Position &position)
{

}

void Shogi::promotePiece(Position &position)
{

}

void Shogi::dropPiece(PieceType pt)
{

}

Board *Shogi::getBoard()
{
    return this->board;
}

void Shogi::getGameStatus()
{

}

Shogi::~Shogi()
{
    delete this->board;
}

