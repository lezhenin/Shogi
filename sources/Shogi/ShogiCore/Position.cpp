#include "Position.h"
#include <cstdlib>
#include <stdexcept>
#include "constants.h"

Position::Position(const int h, const int v)
{
    if(v <= BOARD_WIDTH && h <= BOARD_HEIGHT)
    {
        this->vertical = v;
        this->horizontal = h;
    }

}

int Position::getVertical() const
{
    return this->vertical;
}

int Position::getHorizontal() const
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

