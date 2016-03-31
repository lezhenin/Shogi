#include "GameLoader.h"


void GameLoader::loadGame(AbstractBoard &board)
{
    Save newGame;
    for(int i = 1; i<=9; i++)
    {
        newGame.onBoard.push_back(Block(Pawn, Sente, i, 7));
        newGame.onBoard.push_back(Block(Pawn, Gote, i, 3));
    }
    newGame.onBoard.push_back(Block(Lance,Sente,9,9));
    newGame.onBoard.push_back(Block(Lance,Sente,1,9));
    newGame.onBoard.push_back(Block(Lance,Gote,1,1));
    newGame.onBoard.push_back(Block(Lance,Gote,9,1));

    newGame.onBoard.push_back(Block(Knight,Sente,8,9));
    newGame.onBoard.push_back(Block(Knight,Sente,2,9));
    newGame.onBoard.push_back(Block(Knight,Gote,2,1));
    newGame.onBoard.push_back(Block(Knight,Gote,8,1));

    newGame.onBoard.push_back(Block(SilverGeneral,Sente,7,9));
    newGame.onBoard.push_back(Block(SilverGeneral,Sente,3,9));
    newGame.onBoard.push_back(Block(SilverGeneral,Gote,3,1));
    newGame.onBoard.push_back(Block(SilverGeneral,Gote,7,1));

    newGame.onBoard.push_back(Block(GoldGeneral,Sente,6,9));
    newGame.onBoard.push_back(Block(GoldGeneral,Sente,4,9));
    newGame.onBoard.push_back(Block(GoldGeneral,Gote,4,1));
    newGame.onBoard.push_back(Block(GoldGeneral,Gote,6,1));

    newGame.onBoard.push_back(Block(King,Sente,5,9));
    newGame.onBoard.push_back(Block(King,Gote,5,1));

    newGame.onBoard.push_back(Block(Rook,Sente,2,8));
    newGame.onBoard.push_back(Block(Rook,Gote,8,2));

    newGame.onBoard.push_back(Block(Bishop,Sente,8,8));
    newGame.onBoard.push_back(Block(Bishop,Gote,2,2));

    loadGame(newGame,board);
}

void GameLoader::loadGame(const Save &save, AbstractBoard &board)
{
    for (const Block &b: save.onBoard)
    {
        {
            Piece *tmp = new Piece (b.pieceType,b.player);
            board.setPiece(tmp,Position(b.horizontal,b.vertical));
            board.getAllPieces().push_back(tmp);
        }
    }
    for (const PieceType &pt: save.senteCaptured)
    {
        Piece *tmp = new Piece(pt,Sente);
        board.getSenteCapturedPieces().push_back(tmp);
        board.getAllPieces().push_back(tmp);
    }
    for (const PieceType &pt: save.goteCaptured)
    {
        Piece *tmp = new Piece(pt,Gote);
        board.getGoteCapturedPieces().push_back(tmp);
        board.getAllPieces().push_back(tmp);
    }
}





