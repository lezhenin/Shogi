#ifndef SHOGI_GAMELOGICEXCEPTION_H
#define SHOGI_GAMELOGICEXCEPTION_H

#include <exception>
/**
 * @brief Класс исключений отнясщихся к игровой логике.
 */
class GameLogicException: public std::exception
{

public:
    virtual const char *what() throw() {
        const char* str = "GameLogic exception";
        return str;
    }

};


#endif //SHOGI_GAMELOGICEXCEPTION_H
