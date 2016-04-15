#ifndef SHOGI_JSONSAVEMANAGER_H
#define SHOGI_JSONSAVEMANAGER_H

#include <map>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "../SaveWriter.h"
#include "../SaveReader.h"

/**
 * @brief Класс обеспечивающий создание,
 * чтение и хранение сохранения в формате JSON строк.
 *
 * Класс реализуте интерфейсы SaveReader и SaveWriter.
 */
class JSONSaveManager : public SaveWriter, public SaveReader
{

public:


    JSONSaveManager();
    /**
     * @param JSONString Сохранение в формате JSON строки.
     */
    explicit JSONSaveManager(const std::string &JSONString);

    virtual std::vector<Block> getPiecesOnBoard();
    virtual std::vector<PieceType> getCapturedPieces(const Player &player);

    virtual void addPieceOnBoard(const PieceType pieceType, const Player &player, const Position &position);
    virtual void addCapturedPiece(const Player &player, const PieceType pieceType);

    virtual Player &getCurrentPlayer();

    virtual void setCurrentPlayer(const Player &player);
    /**
     * @brief Получить JSON строку.
     *
     * @return JSON строку содержащую сохранение.
     */
    const std::string getJSONString() const;
    /**
     * @breif Очистить
     *
     * Удаляет внутренне прдеставление доски.
     */
    void clear();

private:

    rapidjson::Document save;

    std::map<PieceType, std::string> tableOfTypes = {{Pawn,          "pawn"},
                                                     {King,          "king"},
                                                     {GoldGeneral,   "golden general"},
                                                     {Rook,          "rook"},
                                                     {Bishop,        "bishop"},
                                                     {SilverGeneral, "silver general"},
                                                     {Knight,        "knight"},
                                                     {Lance,         "lance"}};
    std::map<Player, std::string> tableOfPlayers = {{Sente, "sente"},
                                                    {Gote,  "gote"}};

    std::map<std::string, PieceType> reverseTableOfTypes = {{"pawn",           Pawn},
                                                            {"king",           King},
                                                            {"golden general", GoldGeneral},
                                                            {"rook",           Rook},
                                                            {"bishop",         Bishop},
                                                            {"silver general", SilverGeneral},
                                                            {"knight",         Knight},
                                                            {"lance",          Lance}};
    std::map<std::string, Player> reverseTableOfPlayers = {{"sente", Sente},
                                                           {"gote",  Gote}};
};
#endif //SHOGI_JSONSAVEMANAGER_H
