#include "Player.h"


bool operator == (const Player &left, const Player &right)
{
    return left.playerType == right.playerType;
}

bool operator != (const Player &left, const Player &right)
{
    return left.playerType != right.playerType;
}

bool operator > (const Player &left, const Player &right)
{
    return left.playerType > right.playerType;
}

bool operator < (const Player &left, const Player &right)
{
    return left.playerType < right.playerType;
}
