#ifndef SHOGI_MODELEXCEPTION_H
#define SHOGI_MODELEXCEPTION_H

#include <exception>

namespace shogi
{
    /**
     * @brief Класс исключения, возбуждаемого при
     * возникновении ошибки связанной с игровой моделью.
     */
    class ModelException : public std::exception
    {

    public:
        virtual const char *what() const throw()
        {
            return "Game model exception";
        }
    };
}

#endif //SHOGI_MODELEXCEPTION_H
