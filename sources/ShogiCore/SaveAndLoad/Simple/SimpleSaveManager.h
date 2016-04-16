#ifndef SHOGI_SIMPLESAVEMANAGER_H
#define SHOGI_SIMPLESAVEMANAGER_H

#include "../SaveReader.h"
#include "../SaveWriter.h"
#include "SimpleSave.h"

namespace shogi
{
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
        virtual std::vector<PieceType> getCapturedPieces(const Player &player);

        virtual void addPieceOnBoard(const PieceType pieceType, const Player &player, const Position &position);
        virtual void addCapturedPiece(const Player &player, const PieceType pieceType);
        virtual void setCurrentPlayer(const Player &player);

        virtual Player &getCurrentPlayer();

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
}

#endif //SHOGI_SIMPLESAVEMANAGER_H
