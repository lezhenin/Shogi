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

    static const int BOARD_WIDTH = 9;
    static const int BOARD_HEIGHT = 9;
    static const int PROMOTION_AREA_SIZE = 3;
    static const int PROMOTION_LINE_SENTE = PROMOTION_AREA_SIZE;
    static const int PROMOTION_LINE_GOTE = BOARD_HEIGHT - PROMOTION_AREA_SIZE + 1;

    /**
     * @brief Установить фигуру
     *
     * Устанавливает фигуру на конкретную клетку доски.
     * @param[in] piece Фигура, которая будет установлена.
     * @param[in] pos   Позиция, куда будет установлена фигура
     */
    virtual void setPiece(Piece *piece, const Position &position)=0;

    /**
     * @brief Убрать фигуру
     *
     * Убирает фигуру с клетки доски.
     * @param[in] pos Позиция, откуда будет убрана фигура.
     */
    virtual void removePiece(const Position &position)=0;

    /**
     * @brief Получить фигуру
     *
     * Возвращает фигуру, установленную на клетку доски.
     * @param[in] pos   Позиция где находится фигура.
     * @return Указатель на фигуру.
     */
    virtual Piece *getPiece(const Position &position) const = 0;

    /**
     * @brief Получить мементо.
     *
     * @return Указатель на класс AbstractBoardMemento,
     * в котором сохранено текущее состояние доски.
     */
    virtual AbstractBoardMemento *getMemento() = 0;

    /**
     * @brief Установить мементо.
     *
     * Восстанавливает ранее сохраненное состояние доски.
     * @param memento Указатель на класс AbstractBoardMemento
     */
    virtual void setMemento(AbstractBoardMemento *memento) = 0;

    /**
     * @brief Получить список всех фигур.
     *
     * Возвращает список всех фигур.
     * @return Ссылка на список фигур.
     */
    virtual ListOfPieces &getAllPieces() = 0;

    /**
     * @brief Получить список фигур на доске
     *
     * Возвращает список всех фигур, находящихся на доске
     * @return Ссылка на список фигур.
     */
    virtual ListOfPieces &getPiecesOnBoard() = 0;

    /**
     * @brief Получить список фигур, захваченных одним из игроков
     *
     * Возвращает список всех фигур, захваченных одной из сторон.
     * @param player Игрок, чьи захваченные фигуры необъодимо получить.
     * @return Ссылка на список фигур.
     */
    virtual ListOfPieces &getCapturedPieces(const Player &player) = 0;

    /**
     * @brief Найти фигуру
     *
     * Позволяет найти фигуру в одном из списоков фигур.
     */
    virtual Piece* findPiece(const PieceType pieceType, const Player &player, const ListOfPieces &pieces) const = 0;

    /**
     * @brief Деструктор
     */
    virtual ~AbstractBoard() { }

};


#endif // BOARDINTERFACE_H
