
#include "GameSaver.h"

Save GameSaver::saveGame(AbstractBoard &board)
{
    Save save;
    for (Piece *piece: board.getPiecesOnBoard())
    {
        save.onBoard.push_back(Block(piece->getType(),piece->getPlayer(),
                                     piece->getPosition().getHorizontal(),piece->getPosition().getVertical()));
    }
    for(Piece *piece: board.getCapturedPieces(Sente))
    {
        save.senteCaptured.push_back(piece->getType());
    }
    for(Piece *piece: board.getCapturedPieces(Gote))
    {
        save.goteCaptured.push_back(piece->getType());
    }
    return save;
}