
#ifndef SHOGI_AI_H
#define SHOGI_AI_H

#include "../API/GameAPI.h"
#include "../GameLogic/AbstractGameLogic.h"
#include "../GameLogic/GameLogic.h"

namespace shogi
{
    /**
     * @brief Исскуственный интелект
     *
     * Интерфейс иссукственного интелекта для игры в Сёги.
     */
    class AI
    {
    public:
        /**
         * @param game Объект класса реализующего интерфейс GameAPI.
         */
        AI(GameAPI *game) : game(game) { }
        /**
         * @brief Сделать ход
         *
         * Совершает ход.
         */
        virtual void makeMove() noexcept = 0;

    protected:
        GameAPI *game;

    };

}

#endif //SHOGI_AI_H
