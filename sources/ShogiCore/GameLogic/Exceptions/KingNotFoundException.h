#ifndef SHOGI_KINGNOTFOUNDEXCEPTION_H
#define SHOGI_KINGNOTFOUNDEXCEPTION_H


#include "GameLogicException.h"
/**
 * @brief Класс исключение, выбрасываемого в том случае,
 * если во время проверки шаха или мата не был найден
 * король на доске.
 */
class KingNotFoundException: public GameLogicException
{

public:
    const char *what() throw() {
        const char *str = "King wasn't found";
        return  str;
    }

    virtual ~KingNotFoundException() { }
};


#endif //SHOGI_KINGNOTFOUNDEXCEPTION_H
