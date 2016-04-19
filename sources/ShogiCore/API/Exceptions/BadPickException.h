
#ifndef SHOGI_BAPPICKEXCEPTION_H
#define SHOGI_BAPPICKEXCEPTION_H


#include "GameProcessException.h"

namespace shogi
{
	/**
 	 * @brief Исключение, возбуждаемое при
 	 * попытке выбрать фигуру неправильно.
 	 */
	class BadPickException : public GameProcessException
	{
	public:
		explicit BadPickException(const std::string &message) :
				message(message + ("\nYou can't pick piece at this square.")) { }

	};

}
#endif //SHOGI_BAPPICKEXCEPTION_H
