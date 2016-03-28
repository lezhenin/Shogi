#ifndef SHOGI_ABSTRACTSHOGIGAMELOGIC_H
#define SHOGI_ABSTRACTSHOGIGAMELOGIC_H
#include <map>
#include <vector>
#include <list>
#include "Direction.h"
#include "../Model/AbstractBoard.h"

/**
 * @brief Интерфес класса, содержащего игровую логику и правила игры.
 */
class AbstractShogiGameLogic
{
public:
    /*
     * @brief Проверить возможность хода.
     *
     * @param piece Фигура, ход который будет проверяться.
     * @param pos   Позиция, ход в которую будет проверяться.
     * @return true если ход возможен, false если ход не возможен.
     */
    virtual bool checkMove(Piece *piece, Position pos) const = 0;
    /*
     * @brief Проверить постановку шаха.
     *
     * @param player Игрок, постановка шаха которому будет проверяться.
     * @return true если шах поставлен, false если шах не поставлен.
     */
    virtual bool checkShah(Player player) const = 0;
    /*
     * @brief Проверить постановку мата.
     *
     * @param player Игрок, постановка мата которому будет проверяться.
     * @return true если мат поставлен, false если мат не поставлен.
     */
    virtual bool checkMate(Player player) const = 0;
    /*
     * @brief Проверить возможность переворта.
     *
     * @param piece Фигура, возможность переворота которой будет проверяться.
     * @return true если переворот возможен, false если переворот не возможен.
     */
    virtual bool checkPromotion(Piece *piece) const = 0;
    /*
     * @brief Проверить возможность постановки ранее захваченной фигуры на доску.
     *
     * @param piece Фигура, возможность постановки которой будет проверяться.
     * @param pos Позиция, куда будет выставлятся фигура.
     * @return true если постановка возможена, false если постановка не возможена.
     */
    virtual bool checkDrop(Piece *piece, Position pos) = 0;

};


#endif //SHOGI_ABSTRACTSHOGIGAMELOGIC_H
