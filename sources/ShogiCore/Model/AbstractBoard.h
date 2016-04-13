#ifndef BOARDINTERFACE_H
#define BOARDINTERFACE_H
#include "Square.h"
#include "AbstractBoardMemento.h"
#include <list>

using ListOfPieces = std::list<Piece*>;

/**
 * @brief Интерфейс игровой модели доски
 */
class AbstractBoard
{
public:
    /**
     * @brief Установить фигуру
     *
     * Устанавливает фигуру на конкретную клетку доски.
     * @param[in] piece Фигура, которая будет установлена.
     * @param[in] pos   Позиция, куда будет установлена фигура
     */
    virtual void setPiece(Piece *piece, const Position &pos)=0;
    /**
     * @brief Убрать фигуру
     *
     * Убирает фигуру с клетки доски.
     * @param[in] pos Позиция, откуда будет убрана фигура.
     */
    virtual void removePiece(const Position &pos)=0;
    /**
     * @brief Получить фигуру
     *
     * Возвращает фигуру, установленную на клетку доски.
     * @param[in] pos   Позиция где находится фигура.
     * @return Указатель на фигуру.
     */
        //TODO: это не может быть const?
    virtual Piece *getPiece(const Position &pos)=0;
    /**
     * @brief Получить мементо.
     *
     * @return Указатель на класс AbstractBoardMemento,
     * в котором сохранено текущее состояние доски.
     */
        //TODO: это не может быть const?
    virtual AbstractBoardMemento *getMemento() = 0;
    /**
     * @brief Установить мементо.
     *
     * Восстанавливает ранее сохраненное состояние доски.
     * @param memento Указатель на класс AbstractBoardMemento
     */
    virtual void setMemento(AbstractBoardMemento *memento)=0;\
    /**
     * @brief Получить список всех фигур.
     *
     * Возвращает список всех фигур.
     * @return Ссылка на список фигур.
     */
        //TODO: это не может быть const?
    virtual ListOfPieces &getAllPieces()=0;
    /**
     * @brief Получить список фигур на доске
     *
     * Возвращает список всех фигур, находящихся на доске
     * @return Ссылка на список фигур.
     */
        //TODO: это не может быть const?
    virtual ListOfPieces &getPiecesOnBoard()=0;
    //TODO: почему список фигур sente? это ведь только один из игроков?
    /**
     * @brief Получить список фигур Sente
     *
     * Возвращает список всех фигур, захваченных одной из сторон.
     * @param player Игрок, чьи захваченные фигуры необъодимо получить.
     * @return Ссылка на список фигур.
     */
        //TODO: это не может быть const?
    virtual ListOfPieces &getCapturedPieces(Player player)=0;
    /**
     * @brief Деструктор
     */
    virtual ~AbstractBoard() { }

    static const int BOARD_WIDTH = 9;
    static const int BOARD_HEIGHT = 9;
};



#endif // BOARDINTERFACE_H
