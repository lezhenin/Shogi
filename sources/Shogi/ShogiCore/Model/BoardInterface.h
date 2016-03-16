#ifndef BOARDINTERFACE_H
#define BOARDINTERFACE_H
#include "SquareIsEmptyException.h"
#include "Square.h"
#include <vector>
#include <list>

//todo make alias declaration
typedef std::list<Piece*> Pieces; \

///Интерфес игровой модели доски
class BoardInterface
{
public:

    ///Метод, позволяющий установить фигуру на доску
    virtual void setPiece(Piece *piece, const Position &pos)=0;
    /// Метод, позволяющий удалить фигуру с доски
    virtual void removePiece(const Position &pos)=0;

    ///Метод, позволяющий получить указатель на фигуру по позиции на доске
    virtual Piece *getPiece(const Position &pos)=0;

    ///Метод, позволяющий получить указатели на все фигуры на доске
    virtual Pieces &getPiecesOnBoard()=0;
    ///Метод, позволяющий получить указатели на все фигуры, захваченные сторооной Sente
    virtual Pieces &getSenteCapturedPieces()=0;
    ///Метод, позволяющий получить указатели на все фигуры, захваченные сторооной Gote
    virtual Pieces &getGoteCapturedPieces()=0;
};

#endif // BOARDINTERFACE_H
