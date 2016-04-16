#ifndef SHOGI_SHOGIGAMELOGIC_H
#define SHOGI_SHOGIGAMELOGIC_H

#include "AbstractGameLogic.h"
#include "TableOfDirections.h"

namespace shogi
{
	/**
	 * @brief Реализация AbstractGameLogic.
	 */
	class GameLogic : public AbstractGameLogic
	{
	public:

		explicit GameLogic(AbstractBoard *board) : board(board) { }

		bool checkMove(const Piece *piece, const Position &destination) const;
		bool checkShah(const Player &player) const;
		bool checkMate(const Player &player) const;
		bool checkPromotion(const Piece *piece) const;
		bool checkDrop(Piece *piece, const Position &position) const;

		virtual ~GameLogic() { }

	private:

		bool isUnderAttack(const Player &player, const Position &position) const;
		bool onBoard(const Position &position) const;

		bool checkAbleToMove(const Piece *piece, const Position &position) const;
		bool checkLine(const Piece *pawn, int vertical) const;

		std::vector<Position> getAllPositionToMove(const Piece *piece) const;

		const Direction *findDirection(const Position &source, const Position &destination,
									   const std::vector<Direction> &directions) const;

		AbstractBoard *board;
		TableOfDirections table;

	};
}

#endif //SHOGI_SHOGIGAMELOGIC_H
