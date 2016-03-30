#ifndef SHOGI_BADPOSITIONEXCEPTION_H
#define SHOGI_BADPOSITIONEXCEPTION_H


#include <exception>
#include "ModelException.h"

/**
 * @brief Класс исключения, выбрасываемоего при
 * попытке передать позицию несоответсвующую доске.
 */
class BadPositionException: public ModelException
{

public:
    BadPositionException(){};
    const char* what() const throw()
    {
        return "Position is bad";
    }

};

#endif //SHOGI_BADPOSITIONEXCEPTION_H
