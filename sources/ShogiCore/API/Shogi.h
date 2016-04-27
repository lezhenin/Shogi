#ifndef SHOGI_SHOGI_H
#define SHOGI_SHOGI_H

#include <stack>
#include "GameAPI.h"
#include "../GameLogic/GameSituations/PromotionIsAvailable.h"
#include "../GameLogic/GameSituations/Shah.h"
#include "../GameLogic/GameSituations/Mate.h"
#include "../GameLogic/GameLogic.h"
#include "../SaveAndLoad/GameLoader.h"
#include "../SaveAndLoad/GameSaver.h"
#include "Exceptions/BadPickException.h"
#include "Exceptions/BadMoveException.h"
#include "Exceptions/BadDropException.h"
#include "Exceptions/BadPromoteException.h"

namespace shogi
{

	class Shogi : public GameAPI
	{

	public:

		Shogi() noexcept;

		virtual void pickPiece(const Position &position) override;
		virtual void unPickPiece() noexcept override;
		virtual void movePiece(const Position &destination) override;
		virtual void promotePiece(const Position &position) override;
		virtual void dropPiece(const PieceType pieceType, const Position &position) override;

		virtual bool undo() noexcept override;
		virtual bool redo() noexcept override;

		virtual void save(SaveWriter *saveWriter) noexcept override;
		virtual void load(SaveReader *saveReader) noexcept override;
		virtual void load() noexcept override;

		virtual const Piece *getPickedPiece() const noexcept override;
		virtual Player getCurrentPlayer() const noexcept override;
		virtual AbstractBoard &getBoard() const noexcept override;
		virtual ListOfGameSituations &getGameSituation() noexcept override;
		virtual ~Shogi() noexcept;

	private:

		AbstractBoard *board;
		AbstractGameLogic *gameLogic;
		GameLoader *gameLoader;
		GameSaver *gameSaver;
		ListOfGameSituations gameSituations;
		Piece *pickedPiece = nullptr;
		Player currentPlayer = Sente;

		std::stack<AbstractBoardMemento *> toUndo;
		std::stack<AbstractBoardMemento *> toRedo;

		void clearToUndo() noexcept;
		void clearToRedo() noexcept;
		void clearBoard(AbstractBoard &board) noexcept;
		void checkShahMateGameSituations() noexcept;
		void checkPromoteGameSituation(const Position &position) noexcept;
		void capturePiece(const Position &position) noexcept;

	};
}

#endif //SHOGI_SHOGI_H
