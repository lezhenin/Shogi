#ifndef BOARDINTERFACE_H
#define BOARDINTERFACE_H
#include "SquareIsEmptyException.h"
#include "Square.h"
#include <list>

using ListOfPieces = std::list<Piece*>;

/**
 * /brief Интерфес игровой модели доски
 */
class AbstractBoard
{
public:

    /**
     * Устанавливает фигуру на конкрктную клетку доски.
     * @param[in] piece Фигура, которая будет установлена.
     * @param[in] pos   Позиция куда будет установлена фигура
     */
    virtual void setPiece(Piece *piece, const Position &pos)=0;
    /**
     * Убирает фигуру с клетки доски.
     * @param[in] pos Позиция откуда будет убрана фигура.
     */
    virtual void removePiece(const Position &pos)=0;
    /**
     * Возвращает фигуру, установленную на клетку доски.
     * @param[in] pos   Позиция где находится фигура.
     * @return Указатель на фигуру.
     */
    virtual Piece *getPiece(const Position &pos)=0;
    /**
    * Возвращает список всех фигур, находящихся на доске
    * @return Ссылка на список фигур.
    */
    virtual ListOfPieces &getPiecesOnBoard()=0;
    /*
    * Возвращает список всех фигур, захваченных сторооной Sente
    * @return Ссылка на список фигур.
    */
    virtual ListOfPieces &getSenteCapturedPieces()=0;
    /**
    * Возвращает список всех фигур, захваченных сторооной Gote
    * @return Ссылка на список фигур.
    */
    virtual ListOfPieces &getGoteCapturedPieces()=0;

    virtual ~AbstractBoard() { }
};

#endif // BOARDINTERFACE_H
