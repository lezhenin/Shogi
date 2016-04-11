#ifndef SHOGI_GAMESITUATION_H
#define SHOGI_GAMESITUATION_H
#include <string>

/**
 * @brief Класс, представляющий собобой модель игровой ситуации
 */
class GameSituation
{
public:
    /**
     * @brief Получить сообщение.
     *
     * @return Сообщение о текущей игровой ситуации.
     */
    virtual std::string getMessage()=0;
    /**
     * @brief Узнать завершилась ли игра.
     *
     * @return true если игра завершилась,
     * false если игра продолжается.
     */
    bool isEndOfGame() { return  endOfGame;}
    /**
     * @brief Узнать возможно ли выполнить
     * какое-либо действие, связанное с данным
     * сообщением и игровой ситуацией
     *
     * @return true если есть возможность выполнить
     * действие, false в противном случае.
     */
    bool isExecutable() { return executable;}
    /**
     * @brief Выполнить действие, связанное с данным
     * сообщением и игровой ситуацией
     */
    virtual void execute(){};

protected:
    bool endOfGame = false;
    bool executable = false;
};


#endif //SHOGI_GAMESITUATION_H
