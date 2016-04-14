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

    void setPiece(Piece *piece, const Position &pos);
    void removePiece(const Position &pos);

    Piece *getPiece(const Position &pos) const ;

    AbstractBoardMemento *getMemento();
    void setMemento(AbstractBoardMemento *memento);


    ListOfPieces &getAllPieces();
    ListOfPieces &getPiecesOnBoard();
    ListOfPieces &getCapturedPieces(Player player);

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

    Square *getSquare(const Position &pos) const;
};

#endif // BOARD_H
