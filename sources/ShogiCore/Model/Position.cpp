#include "Position.h"

Position::Position(const int h, const int v)
{
    if(v > 0 && h > 0)
    {
        this->vertical = v;
        this->horizontal = h;
    }
    // todo make exceptions
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

