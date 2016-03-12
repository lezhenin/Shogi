#ifndef SQUAREISEMPTYEXCEPTION_H
#define SQUAREISEMPTYEXCEPTION_H
#include <exception>
#include <string>


class SquareIsEmptyException : public std::exception
{
public:
    SquareIsEmptyException();
    const char* what();
};

#endif // SQUAREISEMPTYEXCEPTION_H
