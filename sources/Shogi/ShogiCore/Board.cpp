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
            squares[i][j] = new Square(Position(i,j));
        }
    }
}

Board::~Board()
{
    for(int i=1; i<=this->height; i++)
    {
        for(int j=1; j<=this->width; j++)
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

