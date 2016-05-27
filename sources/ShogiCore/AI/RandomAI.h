
#ifndef SHOGI_RANDOMAI_H
#define SHOGI_RANDOMAI_H

#include <ctime>
#include "AI.h"

namespace shogi
{
    /**
     * @brief Исскусвенный интелект, делающий случайные ходы.
     *
     * Реализация интерфеса AI
     */
    class RandomAI : public AI
    {
    public:

        RandomAI(GameAPI *game) : AI(game) { std::srand(std::time(0));}

        virtual void makeMove() noexcept override;


    private:

        AbstractGameLogic *logic = new GameLogic(&game->getBoard());

        int random(int min, int max) const noexcept ;

        template<typename T> const
        typename T::iterator get_random(T & list) const noexcept
        {
            auto start = list.begin();
            std::advance(start, random(0,list.size()));
            return start;
        }
    };

}
#endif //SHOGI_RANDOMAI_H
