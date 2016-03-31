#include "Board.h"


Board::Board(int w, int h)
{
    this->width=w;
    this->height=h;

    if(w<=0)
    {
        this->width=1;
    }

    if(h<=0)
    {
        this->height=1;
    }

    createSquares();

}

void Board::setPiece(Piece *piece, const Position &pos)
{
    Square *sq = this->getSquare(pos);
    sq->setPiece(piece);
    piece->setSquare(sq);
    this->onBoard.push_back(piece);

}

void Board::removePiece(const Position &pos)
{
    Square *sq = this->getSquare(pos);
    if(sq->getPiece()!= nullptr)
    {
        this->onBoard.remove(sq->getPiece());
        sq->getPiece()->setSquare(nullptr);
    }
    sq->setPiece(nullptr);
}

inline Square *Board::getSquare(const Position& pos)
{
    return squares[pos.getHorizontal()-1][pos.getVertical()-1];
}

Piece *Board::getPiece(const Position &pos)
{
    return this->getSquare(pos)->getPiece();
}

ListOfPieces &Board::getPiecesOnBoard()
{
    return this->onBoard;
}

ListOfPieces &Board::getSenteCapturedPieces()
{
    return this->SenteCaptured;
}

ListOfPieces &Board::getGoteCapturedPieces()
{
    return this->GoteCaptured;
}

Board::~Board()
{
    deleteSquares();
    deletePieces();
}
AbstractBoardMemento* Board::getMemento()
{
    return new BoardMemento(this);
}

void Board::setMemento(AbstractBoardMemento *memento)
{
    BoardMemento *bm = static_cast<BoardMemento*>(memento);
    bm->restore();
    delete bm;
}

ListOfPieces &Board::getAllPieces()
{
    return allPieces;
}

void Board::createSquares()
{
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

void Board::deleteSquares()
{
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            delete squares[i][j];
        }
    }

    for (int i = 0; i < this->height; i++) {
        delete[] this->squares[i];
    }

    delete[] this->squares;

}


void Board::deletePieces()
{
    for (Piece *p : allPieces)
    {
        delete p;
    }
}



















