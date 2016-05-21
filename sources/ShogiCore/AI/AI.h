
#ifndef SHOGI_AI_H
#define SHOGI_AI_H

#include "../API/GameAPI.h"
#include "../GameLogic/AbstractGameLogic.h"
#include "../GameLogic/GameLogic.h"

namespace shogi {

    class AI
    {
    public:

        AI(GameAPI *game) : game(game) { }
        void makeMove();


    private:

        GameAPI *game;
        AbstractGameLogic *logic = new GameLogic(&game->getBoard());

        int random(int min, int max) const noexcept ;

        template<typename T> const
        typename T::iterator get_random(T & list) const noexcept
        {
            auto start = list.begin();
            std::advance(start, random(0,list.size()-1));
            return start;
        }
    };

}

#endif //SHOGI_AI_H
