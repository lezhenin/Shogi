#include "Position.h"
#include <cstdlib>
#include <stdexcept>
#include "constants.h"

Position::Position(const unsigned int v, const unsigned int h)
{
    if(v <= BOARD_WIDTH && h <= BOARD_HEIGHT)
    {
        this->vertical = v;
    }
    this->horizontal = h;
}

unsigned int Position::getVertical() const
{
    return this->vertical;
}

unsigned int Position::getHorizontal() const
{
    return this->horizontal;
}

bool Position::operator ==(const Position &pos)
{
    return (this->horizontal == pos.horizontal && this->vertical == pos.vertical);
}

Position &Position::operator =(const Position &pos)
{
    if (*this==pos)
    {
        return *this;
    }
    this->horizontal = pos.horizontal;
    this->vertical = pos.vertical;
    return *this;
}

Position::~Position()
{

}

