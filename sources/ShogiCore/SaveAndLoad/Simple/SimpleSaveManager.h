#ifndef SHOGI_SIMPLESAVEMANAGER_H
#define SHOGI_SIMPLESAVEMANAGER_H

#include "../SaveReader.h"
#include "../SaveWriter.h"
#include "SimpleSave.h"

/**
 * @brief Класс обеспечивающий создание,
 * чтение и хранение сохранения типа SimpleSave.
 *
 * Класс реализуте интерфейсы SaveReader и SaveWriter.
 */
class SimpleSaveManager : public SaveReader, public SaveWriter
{

public:
    /**
     * @param save Объект типа SimpleSave.
     */
    explicit SimpleSaveManager(const SimpleSave &save) : save(save) { }
    SimpleSaveManager() { }

    virtual std::vector<Block> getPiecesOnBoard();
    virtual std::vector<PieceType> getCapturedPieces(Player player);
    virtual void addPieceOnBoard(PieceType pieceType, Player player, Position position);
    virtual void addCapturedPiece(Player player, PieceType pieceType);
    virtual void setCurrentPlayer(Player player);
    virtual Player getCurrentPlayer();
    /**
     * @brief Получить объект сохранения.
     *
     * @return Объект сохранения SimpleSave.
     */
    SimpleSave *getSimpleSave()
    {
     return &save;
    }

private:
    SimpleSave save;
};


#endif //SHOGI_SIMPLESAVEMANAGER_H
