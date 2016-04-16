#ifndef SHOGI_BADPOSITIONEXCEPTION_H
#define SHOGI_BADPOSITIONEXCEPTION_H

#include <exception>
#include <string>
#include <sstream>
#include <cstring>
#include "ModelException.h"
#include "../AbstractBoard.h"

namespace shogi
{
    /**
     * @brief Класс исключения, возбуждаемого при
     * попытке передать позицию несоответсвующую доске.
     */
    class BadPositionException : public ModelException
    {

    public:
        explicit BadPositionException(const Position &position) : message(
                "Position(" + std::to_string(position.getHorizontal()) + ", "
                            + std::to_string(position.getVertical()) + ") is bad. " +
                "Board size: "  + std::to_string(AbstractBoard::BOARD_HEIGHT) + " x "
                                + std::to_string(AbstractBoard::BOARD_WIDTH) + ".")
        { }

        const char *what() const throw()
        {
            return message.c_str();
        }

    private:
        std::string message;

    };

}
#endif //SHOGI_BADPOSITIONEXCEPTION_H
