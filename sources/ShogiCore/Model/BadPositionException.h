#ifndef SHOGI_BADPOSITIONEXCEPTION_H
#define SHOGI_BADPOSITIONEXCEPTION_H


#include <exception>
/**
 * @brief Класс исключения, выбрасываемоего при
 * попытке передать позицию несоответсвующую доске.
 */
class BadPositionException: public std::exception
{

public:
    BadPositionException(){};
    const char* what();

};

#endif //SHOGI_BADPOSITIONEXCEPTION_H
