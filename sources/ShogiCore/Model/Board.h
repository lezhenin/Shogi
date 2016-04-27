#ifndef BOARD_H
#define BOARD_H

#include <map>
#include "AbstractBoard.h"
#include "BoardMemento.h"

namespace shogi
{
	/**
	 * @brief Модель доски
	 */
	class Board : public AbstractBoard
	{
	public:

		Board(int w = BOARD_WIDTH, int h = BOARD_HEIGHT);

		virtual void setPiece(Piece *piece, const Position &position) override ;
		virtual void removePiece(const Position &pos) override;

		virtual Piece *getPiece(const Position &pos) const override;
		virtual Piece *findPiece(const PieceType pieceType, const Player &player, const ListOfPieces &pieces) const noexcept override;

		virtual AbstractBoardMemento *getMemento() noexcept override;
		virtual void setMemento(AbstractBoardMemento *memento) noexcept override;

		virtual ListOfPieces &getAllPieces() noexcept override;
		virtual ListOfPieces &getPiecesOnBoard() noexcept override;
		virtual ListOfPieces &getCapturedPieces(const Player &player) noexcept override;
		~Board() noexcept;

	private:

		void createSquares() noexcept ;
		void deleteSquares() noexcept ;
		void deletePieces() noexcept ;

		Square ***squares;
		ListOfPieces onBoard;
		ListOfPieces allPieces;
		std::map<Player, ListOfPieces> capturedPieces {{Sente, ListOfPieces()},
													   {Gote,  ListOfPieces()}};

		int width;
		int height;

		Square *getSquare(const Position &position) const;
	};
}
#endif // BOARD_H
