#include "Position.h"
#include "Exceptions/BadPositionException.h"

Position::Position(const int h, const int v) : horizontal(h), vertical(v)
{

}

int Position::getVertical() const
{
    return this->vertical;
}

int Position::getHorizontal() const
{
    return this->horizontal;
}

bool Position::operator ==(const Position &pos) const
{
    return (this->horizontal == pos.horizontal && this->vertical == pos.vertical);
}

Position &Position::operator =(const Position &pos)
{
    if (*this == pos)
    {
        return *this;
    }
    this->horizontal = pos.horizontal;
    this->vertical = pos.vertical;
    return *this;
}

bool Position::operator!=(const Position &pos) const
{
    return !operator==(pos);
}








