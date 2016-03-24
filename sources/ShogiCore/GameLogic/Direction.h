#ifndef SHOGI_DIRECTION_H
#define SHOGI_DIRECTION_H



class Direction {

public:

    Direction(int x, int y, int limit = 0) : x(x),y(y),limit(limit){};
    int getX() const { return x;}
    int getY() const { return y;}
    int getLimit() const {return limit;}

private:
    int x;
    int y;
    int limit;
};

#endif //SHOGI_DIRECTION_H
