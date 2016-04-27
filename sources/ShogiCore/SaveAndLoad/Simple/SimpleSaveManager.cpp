#include "SimpleSaveManager.h"

using namespace shogi;

std::vector<Block> SimpleSaveManager::getPiecesOnBoard() noexcept
{
    return save.onBoard;
}

std::vector<PieceType> SimpleSaveManager::getCapturedPieces(const Player &player) noexcept
{

    if(player == Sente)
    {
        return save.senteCaptured;
    }
    else
    {
        return save.goteCaptured;
    }
}

void SimpleSaveManager::addPieceOnBoard(const PieceType pieceType, const Player &player, const Position &position) noexcept
{
    save.onBoard.push_back(Block(pieceType, player, position));
}

void SimpleSaveManager::addCapturedPiece(const Player &player, const PieceType pieceType) noexcept
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

void SimpleSaveManager::setCurrentPlayer(const Player &player) noexcept
{
    save.currentPlayer = player;
}

const Player &SimpleSaveManager::getCurrentPlayer() noexcept
{
    return save.currentPlayer;
}










