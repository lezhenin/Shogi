#ifndef SHOGI_BADPOSITIONEXCEPTION_H
#define SHOGI_BADPOSITIONEXCEPTION_H


#include <exception>
#include <string>
#include <sstream>
#include <cstring>
#include "ModelException.h"
#include "../AbstractBoard.h"

/**
 * @brief Класс исключения, возбуждаемого при
 * попытке передать позицию несоответсвующую доске.
 */
//TODO: можно сюда добавить поля для хранения подробностей, какая позиция была плохая и почему?
class BadPositionException: public ModelException
{

public:
    explicit BadPositionException(const Position &position) : position(position){}
    const char* what() const throw()
    {
        std::stringstream stringstream;
        stringstream << "Position(" << position.getHorizontal() << ", "
                                    << position.getVertical()   << ") is bad. "
                     << "Board size: " << AbstractBoard::BOARD_HEIGHT << " x "
                                       << AbstractBoard::BOARD_WIDTH  <<  ".";
        return stringstream.str().c_str();
    }

private:
    const Position &position;

};

#endif //SHOGI_BADPOSITIONEXCEPTION_H
