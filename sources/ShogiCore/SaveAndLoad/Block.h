#ifndef SHOGI_BLOCK_H
#define SHOGI_BLOCK_H

#include "../Model/Piece.h"

namespace shogi
{
	/**
	 * @brief Класс хранит информацию о фигуре.
	 *
	 * Класс учавствует при сохранении и загрузки игры.
	 */
	class Block
	{
	public:
		Block(const PieceType pieceType, const Player &player, const Position &position) noexcept : pieceType(pieceType),
																						   player(player),
																						   position(position)
		{ }

		bool operator == (const Block& block) const noexcept
		{
			return (pieceType == block.pieceType &&
					player 	  == block.player    &&
					position  == block.position);
		}
		PieceType pieceType;
		Player player;
		Position position;

	};
}

#endif //SHOGI_BLOCK_H
