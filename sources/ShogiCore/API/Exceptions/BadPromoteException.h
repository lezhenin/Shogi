
#ifndef SHOGI_BADPROMOTEEXCEPTION_H
#define SHOGI_BADPROMOTEEXCEPTION_H


#include "GameProcessException.h"

class BadPromoteException : public GameProcessException
{

public:
    explicit BadPromoteException(const std::string &message) :
            GameProcessException(message + "\nYou can't promote this piece") { }

};


#endif //SHOGI_BADPROMOTEEXCEPTION_H
