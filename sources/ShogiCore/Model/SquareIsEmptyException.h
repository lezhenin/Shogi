#ifndef SQUAREISEMPTYEXCEPTION_H
#define SQUAREISEMPTYEXCEPTION_H
#include <exception>
#include <string>

/**
 * @brief Класс исключения, выбрасываемоего при попытки
 * обратится к несуществующей фигуре на клетке доски.
 */
class SquareIsEmptyException : public std::exception
{
public:
    SquareIsEmptyException();
    const char* what();
};

#endif // SQUAREISEMPTYEXCEPTION_H
