#ifndef SHOGI_SAVE_H
#define SHOGI_SAVE_H

#include <vector>
#include <string>
#include "../../Model/Piece.h"
#include "../Block.h"

namespace shogi
{
	/**
	 * @brief Класс сохранения
	 *
	 * Используется внутри библиотеки,
	 * не имеет внешнего представления.
	 */
	class SimpleSave
	{
	public:

		SimpleSave() { }

		Player currentPlayer = Sente;
		std::vector<Block> onBoard;
		std::vector<PieceType> senteCaptured;
		std::vector<PieceType> goteCaptured;

	};
}

#endif //SHOGI_SAVE_H
