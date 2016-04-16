#ifndef SHOGI_GAMEPROCCESEXCEPTIONS_H
#define SHOGI_GAMEPROCCESEXCEPTIONS_H


#include <exception>
#include <string>

/**
 * @brief Класс исключения, возбуждаемого
 * во время игрового процесса.
 *
 * Исключение такого типа возбуждается
 * при попытке соверщить неверное действие
 * в ходе игрового процесса.
 */
class GameProcessException : public std::exception
{

public:

    explicit GameProcessException(const std::string &message) : message(message + "\nGame process exception") { }

    virtual const char *what() const throw()
    {
        return message.c_str();
    }

protected:
    std::string message;
};


#endif //SHOGI_GAMEPROCCESEXCEPTIONS_H
