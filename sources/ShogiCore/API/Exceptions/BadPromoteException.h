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
		explicit BadPromoteException(const std::string &message) :
				message(message + "\nYou can't promote this piece") { }

	};
}

#endif //SHOGI_BADPROMOTEEXCEPTION_H
