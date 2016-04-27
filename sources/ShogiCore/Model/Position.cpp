#include "Position.h"
#include "Exceptions/BadPositionException.h"

using namespace shogi;

Position::Position(const int horizontal, const int vertical) noexcept : horizontal(horizontal), vertical(vertical)
{

}

int Position::getVertical() const noexcept
{
    return this->vertical;
}

int Position::getHorizontal() const noexcept
{
    return this->horizontal;
}

bool Position::operator ==(const Position &position) const noexcept
{
    return (this->horizontal == position.horizontal && this->vertical == position.vertical);
}

Position &Position::operator =(const Position &position) noexcept
{
    if (*this == position)
    {
        return *this;
    }
    this->horizontal = position.horizontal;
    this->vertical = position.vertical;
    return *this;
}

bool Position::operator!=(const Position &position) const noexcept
{
    return !operator==(position);
}








