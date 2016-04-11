#include "GameLoader.h"
#include "Simple/SimpleSaveManager.h"


void GameLoader::loadGame(AbstractBoard &board, Player *currentPlayer)
{
    SimpleSaveManager *newGame = new SimpleSaveManager();

    for(int i = 1; i<=9; i++)
    {
        newGame->addPieceOnBoard(Pawn, Sente, Position(7, i));
        newGame->addPieceOnBoard(Pawn, Gote, Position(3, i));
    }
    newGame->addPieceOnBoard(Lance,Sente,Position(9, 9));
    newGame->addPieceOnBoard(Lance,Sente,Position(9, 1));
    newGame->addPieceOnBoard(Lance,Gote,Position(1, 1));
    newGame->addPieceOnBoard(Lance,Gote,Position(1, 9));

    newGame->addPieceOnBoard(Knight,Sente,Position(9, 8));
    newGame->addPieceOnBoard(Knight,Sente,Position(9, 2));
    newGame->addPieceOnBoard(Knight,Gote,Position(1, 8));
    newGame->addPieceOnBoard(Knight,Gote,Position(1, 2));

    newGame->addPieceOnBoard(SilverGeneral,Sente,Position(9, 7));
    newGame->addPieceOnBoard(SilverGeneral,Sente,Position(9, 3));
    newGame->addPieceOnBoard(SilverGeneral,Gote,Position(1, 3));
    newGame->addPieceOnBoard(SilverGeneral,Gote,Position(1, 7));

    newGame->addPieceOnBoard(GoldGeneral,Sente,Position(9, 6));
    newGame->addPieceOnBoard(GoldGeneral,Sente,Position(9, 4));
    newGame->addPieceOnBoard(GoldGeneral,Gote,Position(1, 4));
    newGame->addPieceOnBoard(GoldGeneral,Gote,Position(1, 6));

    newGame->addPieceOnBoard(King,Sente,Position(9, 5));
    newGame->addPieceOnBoard(King,Gote,Position(1, 5));

    newGame->addPieceOnBoard(Rook,Sente,Position(8, 2));
    newGame->addPieceOnBoard(Rook,Gote,Position(2, 8));

    newGame->addPieceOnBoard(Bishop,Sente,Position(8, 8));
    newGame->addPieceOnBoard(Bishop,Gote,Position(2, 2));

    loadGame(newGame,board, currentPlayer);
    delete newGame;

}

void GameLoader::loadGame(SaveReader *saveReader, AbstractBoard &board, Player *currentPlayer)
{
    *currentPlayer = saveReader->getCurrentPlayer();
    for (const Block &b: saveReader->getPiecesOnBoard())
    {
        {
            Piece *tmp = new Piece (b.pieceType,b.player);
            board.setPiece(tmp,b.position);
            board.getAllPieces().push_back(tmp);
        }
    }
    for (const PieceType &pt: saveReader->getCapturedPieces(Sente))
    {
        Piece *tmp = new Piece(pt,Sente);
        board.getCapturedPieces(Sente).push_back(tmp);
        board.getAllPieces().push_back(tmp);
    }
    for (const PieceType &pt: saveReader->getCapturedPieces(Gote))
    {
        Piece *tmp = new Piece(pt,Gote);
        board.getCapturedPieces(Gote).push_back(tmp);
        board.getAllPieces().push_back(tmp);
    }
}





