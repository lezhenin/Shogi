#ifndef SHOGI_GAMEPROCCESEXCEPTIONS_H
#define SHOGI_GAMEPROCCESEXCEPTIONS_H


#include <exception>
#include <string>

namespace shogi
{
	/**
	 * @brief Класс исключения, возбуждаемого
	 * во время игрового процесса.
	 *
	 * Исключение такого типа возбуждается
	 * при попытке соверщить неверное действие
	 * в ходе игрового процесса.
 	 */
	class GameProcessException : public std::exception
	{

	public:

		explicit GameProcessException() {}
		explicit GameProcessException(const std::string &message) : message(message) {}

		virtual const char *what() const throw()
		{
			return message.c_str();
		}

	protected:
		std::string message;
	};
}
#endif //SHOGI_GAMEPROCCESEXCEPTIONS_H
