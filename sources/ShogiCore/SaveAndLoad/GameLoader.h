#ifndef SHOGI_GAMELOADER_H
#define SHOGI_GAMELOADER_H

#include "../Model/AbstractBoard.h"
#include "SaveWriter.h"
#include "SaveReader.h"

/**
 * @brief Класс дял загрузки игры
 *
 * Загружает игру, используя объекты
 * поддерживающие интерфейс SaveReader.
 */
class GameLoader
{
public:
    /**
     * @brief Загрузить игру
     *
     * Загружает игру, используя объекты
     * поддерживающие интерфейс SaveReader.
     */
    virtual void loadGame(SaveReader *saveReader, AbstractBoard &board);
    /**
     * @brief Загрузить игру
     *
     * Загружает игру, устанавливая фигуры в
     * соответствии со стандартной расстоновкой
     * в начале партии.
     */
    virtual void loadGame(AbstractBoard &board);

};

#endif //SHOGI_GAMELOADER_H
