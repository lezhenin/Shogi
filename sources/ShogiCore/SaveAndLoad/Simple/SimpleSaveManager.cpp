#include "SimpleSaveManager.h"

std::vector<Block> SimpleSaveManager::getPiecesOnBoard()
{
    return save.onBoard;
}

std::vector<PieceType> SimpleSaveManager::getCapturedPieces(Player player)  {
    if(player == Sente)
    {
        return save.senteCaptured;
    }
    else
    {
        return save.goteCaptured;
    }
}

void SimpleSaveManager::addPieceOnBoard(PieceType pieceType, Player player, Position position)
{
    save.onBoard.push_back(Block(pieceType, player, position));
}

void SimpleSaveManager::addCapturedPiece(Player player, PieceType pieceType)
{
    if(player == Sente)
    {
        save.senteCaptured.push_back(pieceType);
    }
    if(player == Gote)
    {
        save.goteCaptured.push_back(pieceType);
    }
}

void SimpleSaveManager::setCurrentPlayer(Player player)
{
    save.currentPlayer = player;
}

Player SimpleSaveManager::getCurrentPlayer()
{
    return save.currentPlayer;
}










