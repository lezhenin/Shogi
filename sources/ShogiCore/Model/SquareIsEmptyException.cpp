#include "SquareIsEmptyException.h"

SquareIsEmptyException::SquareIsEmptyException()
{

}

const char *SquareIsEmptyException::what()
{
    const char* str =  "Square is empty";
    return str;
}

