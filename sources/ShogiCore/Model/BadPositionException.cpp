#include "BadPositionException.h"

const char* BadPositionException::what()
{
    return "Position is bad";
}