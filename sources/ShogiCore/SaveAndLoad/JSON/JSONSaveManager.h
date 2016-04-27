#ifndef SHOGI_JSONSAVEMANAGER_H
#define SHOGI_JSONSAVEMANAGER_H

#include <map>
#include "rapidjson/document.h"
#include "../SaveWriter.h"
#include "../SaveReader.h"

namespace shogi {
    /**
     * @brief Класс обеспечивающий создание,
     * чтение и хранение сохранения в формате JSON строк.
     *
     * Класс реализуте интерфейсы SaveReader и SaveWriter.
     */
    class JSONSaveManager : public SaveWriter, public SaveReader {

    public:


        JSONSaveManager() noexcept;

        /**
		 * @param JSONString Сохранение в формате JSON строки.
		 */
        explicit JSONSaveManager(const std::string &JSONString);

        virtual std::vector<Block> getPiecesOnBoard() noexcept override;

        virtual std::vector<PieceType> getCapturedPieces(const Player &player) noexcept override;

        virtual void addPieceOnBoard(const PieceType pieceType, const Player &player,
                                     const Position &position) noexcept override;

        virtual void addCapturedPiece(const Player &player, const PieceType pieceType) noexcept override;

        virtual Player &getCurrentPlayer() noexcept override;

        virtual void setCurrentPlayer(const Player &player) noexcept override;

        /**
		 * @brief Получить JSON строку.
		 *
		 * @return JSON строку содержащую сохранение.
		 */
        const std::string getJSONString() const noexcept;

        /**
		 * @breif Очистить
		 *
		 * Удаляет внутренне прдеставление доски.
		 */
        void clear() noexcept;

    private:

        rapidjson::Document save;

        std::map<PieceType, std::string> tableOfTypes = {{Pawn,                  "pawn"},
                                                         {King,                  "king"},
                                                         {GoldGeneral,           "golden general"},
                                                         {Rook,                  "rook"},
                                                         {Bishop,                "bishop"},
                                                         {SilverGeneral,         "silver general"},
                                                         {Knight,                "knight"},
                                                         {Lance,                 "lance"},
                                                         {PromotedRook,          "promoted rook"},
                                                         {PromotedBishop,        "promoted bishop"},
                                                         {PromotedSilverGeneral, "promoted silver general"},
                                                         {PromotedKnight,        "promoted knight"},
                                                         {PromotedLance,         "promoted lance"},
                                                         {PromotedPawn,          "promoted pawn"}};
        std::map<Player, std::string> tableOfPlayers = {{Sente, "sente"},
                                                        {Gote,  "gote"}};
        std::map<std::string, PieceType> reverseTableOfTypes = {{"pawn",                    Pawn},
                                                                {"king",                    King},
                                                                {"golden general",          GoldGeneral},
                                                                {"rook",                    Rook},
                                                                {"bishop",                  Bishop},
                                                                {"silver general",          SilverGeneral},
                                                                {"knight",                  Knight},
                                                                {"lance",                   Lance},
                                                                {"promoted rook",           PromotedRook},
                                                                {"promoted bishop",         PromotedBishop},
                                                                {"promoted silver general", PromotedSilverGeneral},
                                                                {"promoted knight",         PromotedKnight},
                                                                {"promoted lance",          PromotedLance},
                                                                {"promoted pawn",           PromotedPawn}};
        std::map<std::string, Player> reverseTableOfPlayers = {{"sente", Sente},
                                                               {"gote",  Gote}};
    };
}

#endif //SHOGI_JSONSAVEMANAGER_H