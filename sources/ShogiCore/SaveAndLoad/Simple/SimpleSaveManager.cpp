#include "SimpleSaveManager.h"

std::vector<Block> SimpleSaveManager::getPiecesOnBoard()
{
    return save.onBoard;
}

std::vector<PieceType> SimpleSaveManager::getCapturedPieces(const Player player)  {
    if(player == Sente)
    {
        return save.senteCaptured;
    }
    else
    {
        return save.goteCaptured;
    }
}

void SimpleSaveManager::addPieceOnBoard(const PieceType pieceType, const Player player, const Position &position)
{
    save.onBoard.push_back(Block(pieceType, player, position));
}

void SimpleSaveManager::addCapturedPiece(const Player player, const PieceType pieceType)
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

void SimpleSaveManager::setCurrentPlayer(const Player player)
{
    save.currentPlayer = player;
}

Player SimpleSaveManager::getCurrentPlayer()
{
    return save.currentPlayer;
}










