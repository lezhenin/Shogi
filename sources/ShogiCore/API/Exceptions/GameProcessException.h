#ifndef SHOGI_GAMEPROCCESEXCEPTIONS_H
#define SHOGI_GAMEPROCCESEXCEPTIONS_H


#include <exception>
#include <string>

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
