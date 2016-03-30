#ifndef SQUAREISEMPTYEXCEPTION_H
#define SQUAREISEMPTYEXCEPTION_H
#include <exception>
#include <string>
#include "ModelException.h"

/**
 * @brief Класс исключения, выбрасываемоего при попытки
 * обратится к несуществующей фигуре на клетке доски.
 */
class SquareIsEmptyException : public ModelException
{
public:
    const char* what() const throw()
    {
        const char* str =  "Square is empty";
    }
};

#endif // SQUAREISEMPTYEXCEPTION_H
