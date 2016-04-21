#ifndef SHOGI_PIECEISNOTONBOARDEXCEPTION_H
#define SHOGI_PIECEISNOTONBOARDEXCEPTION_H

#include "ModelException.h"

namespace shogi
{
    /**
     * @brief Класс исключения, возбуждаемого при
     * возникновении ошибки связанной с игровой моделью.
     */
    class PieceIsNotOnBoardException : public ModelException
    {

    public:
        virtual const char *what() const throw() {
            return "Piece is not on the board.";
        }
    };
}

#endif //SHOGI_PIECEISNOTONBOARDEXCEPTION_H
