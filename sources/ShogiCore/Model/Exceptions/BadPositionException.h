#ifndef SHOGI_BADPOSITIONEXCEPTION_H
#define SHOGI_BADPOSITIONEXCEPTION_H


#include <exception>
#include "ModelException.h"

/**
 * @brief Класс исключения, возбуждаемого при
 * попытке передать позицию несоответсвующую доске.
 */
//TODO: можно сюда добавить поля для хранения подробностей, какая позиция была плохая и почему?
class BadPositionException: public ModelException
{

public:
    BadPositionException(const Position &position){}
    const char* what() const throw()
    {
        return "Position is bad";
    }

};

#endif //SHOGI_BADPOSITIONEXCEPTION_H
