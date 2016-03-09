#include "Board.h"

Board::Board(int w, int h)
{
    this->width=w;
    this->height=h;

    this->squares = new Square **[this->height];
    for(int i=0; i<this->height; i++)
    {
        this->squares[i] = new Square *[this->width];
    }

    for(int i=1; i<=this->height; i++)
    {
        for(int j=1; j<=this->width; j++)
        {
            squares[i-1][j-1] = new Square(Position(i,j));
        }
    }
}

void Board::setPiece(Piece *piece, const Position &pos)
{
    Square *sq = this->getSquare(pos);
    sq->setPiece(piece);
    piece->setSquare(sq);

}

void Board::removePiece(const Position &pos)
{
    Square *sq = this->getSquare(pos);
    if(sq->getPiece()!=0)
    {
        sq->getPiece()->setSquare(0);
    }
    sq->setPiece(0);
}

inline Square *Board::getSquare(const Position& pos)
{
    return squares[pos.getHorizontal()-1][pos.getVertical()-1];
}

Pieces &Board::getPiecesOnBoard()
{
    return this->onBoard;
}

Pieces &Board::getSenteCapturedPieces()
{
    return this->SenteCaptured;
}

Pieces &Board::getGoteCapturedPieces()
{
    return this->GoteCaptured;
}

Board::~Board()
{
    for(int i=0; i < this->height; i++)
    {
        for(int j=0; j < this->width; j++)
        {
            delete squares[i][j];
        }
    }

    for(int i=0; i<this->height; i++)
    {
        delete [] this->squares[i];
    }

    delete [] this->squares;
}

