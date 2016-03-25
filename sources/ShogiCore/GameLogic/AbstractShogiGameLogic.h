#ifndef SHOGI_ABSTRACTSHOGIGAMELOGIC_H
#define SHOGI_ABSTRACTSHOGIGAMELOGIC_H
#include <map>
#include <vector>
#include <list>
#include "Direction.h"
#include "../Model/AbstractBoard.h"

class AbstractShogiGameLogic
{
public:
    virtual bool checkMove(Piece *piece, Position pos) const = 0;

    virtual bool checkShah(Player player) = 0;

    virtual bool checkMate() = 0;

};


#endif //SHOGI_ABSTRACTSHOGIGAMELOGIC_H
