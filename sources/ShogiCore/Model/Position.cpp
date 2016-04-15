#include "Position.h"
#include "Exceptions/BadPositionException.h"

Position::Position(const int horizontal, const int vertical) : horizontal(horizontal), vertical(vertical)
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

bool Position::operator ==(const Position &position) const
{
    return (this->horizontal == position.horizontal && this->vertical == position.vertical);
}

Position &Position::operator =(const Position &position)
{
    if (*this == position)
    {
        return *this;
    }
    this->horizontal = position.horizontal;
    this->vertical = position.vertical;
    return *this;
}

bool Position::operator!=(const Position &position) const
{
    return !operator==(position);
}








