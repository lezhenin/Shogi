#ifndef SHOGI_JSONSAVEMANAGER_H
#define SHOGI_JSONSAVEMANAGER_H

#include <map>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "../SaveWriter.h"
#include "../SaveReader.h"

class JSONSaveManager : public SaveWriter, public SaveReader
{

public:


    JSONSaveManager();

    JSONSaveManager(const std::string &JSONString);

    virtual std::vector<Block> getPiecesOnBoard();

    virtual std::vector<PieceType> getCapturedPieces(Player player);

    virtual void addPieceOnBoard(PieceType pieceType, Player player, Position position);

    virtual void addCapturedPiece(Player player, PieceType pieceType);

    const std::string getJSONString() const;

private:

    rapidjson::Document save;
    std::string JSONString;

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
