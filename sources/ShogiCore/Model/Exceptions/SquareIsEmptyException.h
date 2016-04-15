#ifndef SQUAREISEMPTYEXCEPTION_H
#define SQUAREISEMPTYEXCEPTION_H
#include <exception>
#include <string>
#include "ModelException.h"
#include "../Position.h"

/**
 * @brief Класс исключения, возбуждаемого при попытке
 * обратиться к несуществующей фигуре на клетке доски.
 */
class SquareIsEmptyException : public ModelException
{

public:
    explicit SquareIsEmptyException(const Position& position) : message(
            "Square(" + std::to_string(position.getHorizontal()) + ", "
                      + std::to_string(position.getVertical())   + ") is empty." ) {}


    const char* what() const throw()
    {
        return message.c_str();
    }

private:
    std::string message;
};

#endif // SQUAREISEMPTYEXCEPTION_H
