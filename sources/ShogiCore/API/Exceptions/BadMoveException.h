
#ifndef SHOGI_BADMOVIEEXCEPTION_H
#define SHOGI_BADMOVIEEXCEPTION_H


#include "GameProcessException.h"

class BadMoveException : public GameProcessException
{

public:
    explicit BadMoveException(const std::string &message ) :
            GameProcessException(message + ("\nYou can't movie this piece here.")) { }

};


#endif //SHOGI_BADMOVIEEXCEPTION_H
