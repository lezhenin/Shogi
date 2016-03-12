#include "SquareIsEmptyException.h"

SquareIsEmptyException::SquareIsEmptyException()
{

}

const char *SquareIsEmptyException::what()
{
    std::string s = "Square is empty";
    return s.c_str();
}

