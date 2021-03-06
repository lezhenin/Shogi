#include <algorithm>
#include "Board.h"
#include "Exceptions/BadPositionException.h"

using namespace shogi;

Board::Board(int w, int h)
{
    this->width = w;
    this->height = h;

    if(w <= 0)
    {
        this->width=1;
    }

    if(h <= 0)
    {
        this->height=1;
    }

    createSquares();

}

void Board::setPiece(Piece *piece, const Position &position)
{
    if (position.getHorizontal() < 1 || position.getHorizontal() > height ||
        position.getVertical()   < 1 || position.getVertical()   > width)
    {
        throw BadPositionException(position);
    }
    Square *sq = this->getSquare(position);
    sq->setPiece(piece);
    piece->setSquare(sq);
    this->onBoard.push_back(piece);

}

void Board::removePiece(const Position &pos)
{
    Square *sq = this->getSquare(pos);
    if(sq->getPiece() != nullptr)
    {
        this->onBoard.remove(sq->getPiece());
        sq->getPiece()->setSquare(nullptr);
    }
    sq->setPiece(nullptr);
}

inline Square *Board::getSquare(const Position& position) const
{
    if (position.getHorizontal() < 1 || position.getHorizontal() > height ||
        position.getVertical()   < 1 || position.getVertical()   > width)
    {
        throw BadPositionException(position);
    }
    return squares[position.getHorizontal() - 1][position.getVertical() - 1];
}

Piece *Board::getPiece(const Position &pos) const
{
    try
    {
        return this->getSquare(pos)->getPiece();
    }
    catch (BadPositionException &e)
    {
        throw;
    }
}

ListOfPieces &Board::getPiecesOnBoard() noexcept
{
    return this->onBoard;
}

Board::~Board()
{
    deleteSquares();
    deletePieces();
}
AbstractBoardMemento* Board::getMemento() noexcept
{
    return new BoardMemento(this);
}

void Board::setMemento(AbstractBoardMemento *memento) noexcept
{
    BoardMemento *bm = static_cast<BoardMemento*>(memento);
    bm->restore();
}

ListOfPieces &Board::getAllPieces() noexcept
{
    return allPieces;
}

void Board::createSquares() noexcept
{
    this->squares = new Square **[this->height];
    for(int i = 0; i < this->height; i++)
    {
        this->squares[i] = new Square *[this->width];
    }

    for(int i = 1; i <= this->height; i++)
    {
        for(int j = 1; j <= this->width; j++)
        {
            squares[i - 1][j - 1] = new Square(Position(i, j));
        }
    }
}

void Board::deleteSquares() noexcept
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


void Board::deletePieces() noexcept
{
    for (Piece *p : allPieces)
    {
        delete p;
    }
}

ListOfPieces &Board::getCapturedPieces(const Player &player) noexcept
{
    return this->capturedPieces.at(player);
}

Piece *Board::findPiece(const PieceType pieceType, const Player &player, const ListOfPieces &pieces) const noexcept
{
    Piece samplePiece(pieceType,player);

    ListOfPieces::const_iterator iterator =
            std::find_if(pieces.begin(), pieces.end(),[&samplePiece](Piece *piece)
                                                        {
                                                            return piece->equals(samplePiece);
                                                        });
    if (iterator != pieces.end())
    {
        return *iterator;
    }
    else
    {
        return nullptr;
    }
}























