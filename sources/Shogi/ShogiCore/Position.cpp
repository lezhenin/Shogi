#include "Position.h"
#include <cstdlib>
#include <stdexcept>
#include "constants.h"

Position::Position(unsigned int v, unsigned int h)
{
    if(v <= BOARD_WIDTH && h <= BOARD_HEIGHT)
        this->vertical = v;
    this->horizontal = h;
}

Position &Position::operator =(Position &pos)
{
    if (pos==*this){
        return *this;
    }
    this->horizontal = pos.horizontal;
    this->vertical = pos.vertical;
    return *this;
}

