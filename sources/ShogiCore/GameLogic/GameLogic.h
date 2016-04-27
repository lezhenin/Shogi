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

		bool checkMove(const Piece *piece, const Position &destination) const noexcept override;
		bool checkShah(const Player &player) const override;
		bool checkMate(const Player &player) const override;
		bool checkPromotion(const Piece *piece) const noexcept override;
		bool checkDrop(Piece *piece, const Position &position) const noexcept override;

		virtual ~GameLogic() noexcept { }

	private:

		bool isUnderAttack(const Player &player, const Position &position) const noexcept;
		bool onBoard(const Position &position) const noexcept;

		bool checkAbleToMove(const Piece *piece, const Position &position) const noexcept;
		bool checkLine(const Piece *pawn, int vertical) const noexcept;

		std::vector<Position> getAllPositionToMove(const Piece *piece) const noexcept;

		const Direction *findDirection(const Position &source, const Position &destination,
									   const std::vector<Direction> &directions) const noexcept;

		AbstractBoard *board;
		TableOfDirections table;

	};
}

#endif //SHOGI_SHOGIGAMELOGIC_H
