#ifndef SHOGI_GAMESAVER_H
#define SHOGI_GAMESAVER_H

#include "SaveWriter.h"
#include "../Model/AbstractBoard.h"

namespace shogi
{
    /**
     * @brief Класс дял загрузки игры
     *
     * Загружает игру, используя объекты
     * поддерживающие интерфейс SaveWriter.
     */
    class GameSaver
    {
    public:

        /**
		 * @brief Сохранить игру
		 *
		 * Загружает игру, используя объекты
		 * поддерживающие интерфейс SaveWriter.
		 */
        void saveGame(SaveWriter *saveWriter, AbstractBoard &board, Player *currentPlayer);

    };
}

#endif //SHOGI_GAMESAVER_H
