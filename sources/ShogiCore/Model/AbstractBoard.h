#ifndef BOARDINTERFACE_H
#define BOARDINTERFACE_H
#include "Square.h"
#include "AbstractBoardMemento.h"
#include <list>

using ListOfPieces = std::list<Piece*>;

/**
 * @brief Интерфес игровой модели доски
 */
class AbstractBoard
{
public:

    /**
     * @brief Установить фигуру
     *
     * Устанавливает фигуру на конкрктную клетку доски.
     * @param[in] piece Фигура, которая будет установлена.
     * @param[in] pos   Позиция куда будет установлена фигура
     */
    virtual void setPiece(Piece *piece, const Position &pos)=0;
    /**
     * @brief Убрать фигуру
     *
     * Убирает фигуру с клетки доски.
     * @param[in] pos Позиция откуда будет убрана фигура.
     */
    virtual void removePiece(const Position &pos)=0;
    /**
     * @brief Поулчить фигуру
     *
     * Возвращает фигуру, установленную на клетку доски.
     * @param[in] pos   Позиция где находится фигура.
     * @return Указатель на фигуру.
     */
    virtual Piece *getPiece(const Position &pos)=0;
    /**
     * @brief Получить список фигур на доске
     *
     * Возвращает список всех фигур, находящихся на доске
     * @return Ссылка на список фигур.
     */
    virtual AbstractBoardMemento *getMemento() = 0;

    virtual void setMemento(AbstractBoardMemento *memento)=0;

    virtual ListOfPieces &getPiecesOnBoard()=0;
    /*
     * @brief Получить список фигур Sente
     *
     * Возвращает список всех фигур, захваченных сторооной Sente
     * @return Ссылка на список фигур.
     */
    virtual ListOfPieces &getSenteCapturedPieces()=0;
    /**
     * @brief Получить список фигур Gote
     *
     * Возвращает список всех фигур, захваченных сторооной Gote
     * @return Ссылка на список фигур.
     */
    virtual ListOfPieces &getGoteCapturedPieces()=0;
    /**
     * @brief Деструктор
     */
    virtual ~AbstractBoard() { }

    static const int BOARD_WIDTH = 9;
    static const int BOARD_HEIGHT = 9;
};

#endif // BOARDINTERFACE_H
