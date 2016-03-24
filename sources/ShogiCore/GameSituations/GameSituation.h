#ifndef SHOGI_GAMESITUATION_H
#define SHOGI_GAMESITUATION_H
#include <string>


class GameSituation
{
public:

    virtual std::string getMessage()=0;
    bool isEndOfGame() { return  endOfGame;}

protected:
    bool endOfGame = false;
};


#endif //SHOGI_GAMESITUATION_H
