
#ifndef SHOGI_PLAYER_H
#define SHOGI_PLAYER_H

enum PlayerType
{
    Sente = 0, Gote
};
/**
 * @brief Класс содержащий прдеставление игрока.
 */
class Player
{

public:

    Player(PlayerType playerType = Sente) : playerType(playerType) { }

    friend bool operator == (const Player &left, const Player &right);
    friend bool operator != (const Player &left, const Player &right);
    friend bool operator > (const Player &left, const Player &right);
    friend bool operator < (const Player &left, const Player &right);

    /**
     * @brief Слудующий игрок.
     *
     * Возвращает новый объект игрока, отличающийся
     * от того, метод которого был вызван.
     */
    Player nextPlayer() const
    {
        return (*this == Sente) ? Gote : Sente;
    }

    /**
     * @brief Сменить игрока
     *
     * Меняет игрока, внутри объекта, метод
     * которого был вызван.
     */
    void changePlayer()
    {
        playerType = this->nextPlayer().playerType;
    }

private:
    PlayerType playerType;
};



#endif //SHOGI_PLAYER_H
