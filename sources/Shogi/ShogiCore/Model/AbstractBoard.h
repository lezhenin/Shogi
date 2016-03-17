#ifndef BOARDINTERFACE_H
#define BOARDINTERFACE_H
#include "SquareIsEmptyException.h"
#include "Square.h"
#include <list>

//todo make alias declaration
typedef std::list<Piece*> ListOfPieces;

///Интерфес игровой модели доски
class AbstractBoard
{
public:

    ///Метод, позволяющий установить фигуру на доску
    virtual void setPiece(Piece *piece, const Position &pos)=0;
    /// Метод, позволяющий удалить фигуру с доски
    virtual void removePiece(const Position &pos)=0;

    ///Метод, позволяющий получить указатель на фигуру по позиции на доске
    virtual Piece *getPiece(const Position &pos)=0;

    ///Метод, позволяющий получить указатели на все фигуры на доске
    virtual ListOfPieces &getPiecesOnBoard()=0;
    ///Метод, позволяющий получить указатели на все фигуры, захваченные сторооной Sente
    virtual ListOfPieces &getSenteCapturedPieces()=0;
    ///Метод, позволяющий получить указатели на все фигуры, захваченные сторооной Gote
    virtual ListOfPieces &getGoteCapturedPieces()=0;

    virtual ~AbstractBoard() { }
};

#endif // BOARDINTERFACE_H
