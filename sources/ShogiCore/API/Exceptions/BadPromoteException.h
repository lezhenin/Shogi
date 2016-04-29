#ifndef SHOGI_BADPROMOTEEXCEPTION_H
#define SHOGI_BADPROMOTEEXCEPTION_H

#include "GameProcessException.h"

namespace shogi
{
	/**
 	* @brief Исключение, возбуждаемое при
 	* попытке перевернуть фигуру против правил.
	 */
	class BadPromoteException : public GameProcessException
	{

	public:

		BadPromoteException() : GameProcessException("You can't promote this piece") { }
		explicit BadPromoteException(const std::string &message) :
				GameProcessException(message + "\nYou can't promote this piece") { }

	};
}

#endif //SHOGI_BADPROMOTEEXCEPTION_H
