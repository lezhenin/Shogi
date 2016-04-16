
#ifndef SHOGI_BADDROPEXCEPTION_H
#define SHOGI_BADDROPEXCEPTION_H


#include "GameProcessException.h"
/**
 * @brief Исключение, возбуждаемое при
 * попытке выставить фигуру на доску неправильно.
 */
class BadDropException : public GameProcessException
{

public:
    explicit BadDropException(const std::string &message) :
            GameProcessException(message + "\nYou can't drop piece here.") { }

};


#endif //SHOGI_BADDROPEXCEPTION_H
