#ifndef SHOGI_BADMOVIEEXCEPTION_H
#define SHOGI_BADMOVIEEXCEPTION_H

#include "GameProcessException.h"

namespace shogi
{
	/**
	 * @brief Исключение, возбуждаемое при
     * попытке совершить неверный ход.
     */
	class BadMoveException : public GameProcessException
	{

	public:

		BadMoveException() : GameProcessException("You can't movie this piece here.") { }
		explicit BadMoveException(const std::string &message) :
				GameProcessException(message + ("\nYou can't movie this piece here.")) { }

	};

}
#endif //SHOGI_BADMOVIEEXCEPTION_H
