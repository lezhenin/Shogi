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
        explicit SimpleSaveManager(const SimpleSave &save) noexcept : save(save) { }

        SimpleSaveManager() { }

        virtual std::vector<Block> getPiecesOnBoard() noexcept override;
        virtual std::vector<PieceType> getCapturedPieces(const Player &player) noexcept override;

        virtual void addPieceOnBoard(const PieceType pieceType, const Player &player, const Position &position) noexcept override;
        virtual void addCapturedPiece(const Player &player, const PieceType pieceType) noexcept override;
        virtual void setCurrentPlayer(const Player &player) noexcept override;

        virtual const Player &getCurrentPlayer() noexcept override;

        /**
		 * @brief Получить объект сохранения.
		 *
		 * @return Объект сохранения SimpleSave.
		 */
        const SimpleSave *getSimpleSave()const noexcept
        {
            return &save;
        }

    private:
        SimpleSave save;
    };
}

#endif //SHOGI_SIMPLESAVEMANAGER_H
