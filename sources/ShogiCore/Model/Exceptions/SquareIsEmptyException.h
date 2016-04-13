#ifndef SQUAREISEMPTYEXCEPTION_H
#define SQUAREISEMPTYEXCEPTION_H
#include <exception>
#include <string>
#include "ModelException.h"

/**
 * @brief Класс исключения, возбуждаемого при попытке
 * обратиться к несуществующей фигуре на клетке доски.
 */
//TODO: можно сюда добавить поля для хранения подробностей, какая фигура несуществующая на какой клетке?
class SquareIsEmptyException : public ModelException
{
public:
    const char* what() const throw()
    {
        const char* str =  "Square is empty";
    }
};

#endif // SQUAREISEMPTYEXCEPTION_H
