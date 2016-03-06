#ifndef POSITION_H
#define POSITION_H

class Position
{
public:

    Position( unsigned int v, unsigned int h);

    unsigned int getVertical() {return this->vertical;}
    unsigned int getHorizontal() {return this->horizontal;}

    bool operator == (Position& pos) { return (this->horizontal == pos.horizontal && this->vertical == pos.vertical); }

    Position& operator = (Position& pos);

private:
    unsigned int vertical;
    unsigned int horizontal;
};

#endif // POSITION_H
