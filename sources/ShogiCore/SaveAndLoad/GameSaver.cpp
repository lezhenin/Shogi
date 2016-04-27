#include "GameSaver.h"

using namespace shogi;

void GameSaver::saveGame(SaveWriter *saveWriter, AbstractBoard &board, Player *currentPlayer) noexcept
{
    saveWriter->setCurrentPlayer(*currentPlayer);

    for (Piece *piece: board.getPiecesOnBoard())
    {
        saveWriter->addPieceOnBoard(piece->getType(), piece->getPlayer(), piece->getPosition());
    }
    for(Piece *piece: board.getCapturedPieces(Sente))
    {
        saveWriter->addCapturedPiece(Sente, piece->getType());
    }
    for(Piece *piece: board.getCapturedPieces(Gote))
    {
        saveWriter->addCapturedPiece(Gote, piece->getType());
    }
}