#ifndef BOARD_H
#define BOARD_H

#include <map>
#include "AbstractBoard.h"
#include "BoardMemento.h"
/**
 * @brief Модель доски
 * */
class Board: public AbstractBoard
{
public:

    Board(int w = BOARD_WIDTH, int h = BOARD_HEIGHT);

    virtual void setPiece(Piece *piece, const Position &pos);
    virtual void removePiece(const Position &pos);

    virtual Piece *getPiece(const Position &pos) const;
    virtual Piece *findPiece(const PieceType pieceType, const Player player, const ListOfPieces &pieces) const;

    virtual AbstractBoardMemento *getMemento();
    virtual void setMemento(AbstractBoardMemento *memento);

    virtual ListOfPieces &getAllPieces();
    virtual ListOfPieces &getPiecesOnBoard();
    virtual ListOfPieces &getCapturedPieces(Player player);

    ~Board();

private:

    void createSquares();
    void deleteSquares();
    void deletePieces();

    Square ***squares;
    ListOfPieces onBoard;
    ListOfPieces allPieces;
    std::map<Player,ListOfPieces> capturedPieces{{Sente,ListOfPieces()},{Gote,ListOfPieces()}};

    int width;
    int height;

    Square *getSquare(const Position &position) const;
};

#endif // BOARD_H
