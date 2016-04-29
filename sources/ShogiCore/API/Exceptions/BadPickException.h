
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

		BadPickException() : GameProcessException("You can't pick piece at this square.") { }
		explicit BadPickException(const std::string &message) :
				GameProcessException(message + ("\nYou can't pick piece at this square.")) { }

	};

}
#endif //SHOGI_BAPPICKEXCEPTION_H
