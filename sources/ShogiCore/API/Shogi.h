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

		Shogi();

		virtual void pickPiece(const Position &position) override;
		virtual void unPickPiece() override;
		virtual void movePiece(const Position &destination) override;
		virtual void promotePiece(const Position &position) override;
		virtual void dropPiece(const PieceType pieceType, const Position &position) override;

		virtual bool undo() override;
		virtual bool redo() override;

		virtual void save(SaveWriter *saveWriter) override;
		virtual void load(SaveReader *saveReader) override;
		virtual void load() override;

		virtual const Piece *getPickedPiece() const override;
		virtual Player getCurrentPlayer() const override;
		virtual AbstractBoard &getBoard() const override;
		virtual ListOfGameSituations &getGameSituation() override;
		virtual ~Shogi();

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

		void clearToUndo();
		void clearToRedo();
		void clearBoard(AbstractBoard &board);
		void checkShahMateGameSituations();
		void checkPromoteGameSituation(const Position &position);
		void capturePiece(const Position &position);

	};
}

#endif //SHOGI_SHOGI_H
