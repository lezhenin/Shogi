#ifndef SHOGI_JSONSAVEREADER_H
#define SHOGI_JSONSAVEREADER_H


#include <string>
#include <map>
#include "../SaveReader.h"
#include "rapidjson/document.h"

class JSONSaveReader : public SaveReader
{

public:

    explicit JSONSaveReader(const std::string &JSONString) : JSONString(JSONString)
    {
        document.Parse(JSONString.c_str());
    }

    virtual std::vector<Block> getPiecesOnBoard();
    virtual std::vector<PieceType> getCapturedPieces(Player player);

private:
    std::string JSONString;
    rapidjson::Document document;
    std::map<std::string,PieceType> tableOfTypes = {{"pawn", Pawn},{"king", King}, {"golden general", GoldGeneral}, {"rook" ,Rook},
                                                    {"bishop", Bishop}, {"silver general", SilverGeneral}, {"knight", Knight}, {"lance", Lance}};
    std::map<std::string,Player> tableOfPlayers = {{"sente", Sente},{"gote", Gote}};
};


#endif //SHOGI_JSONSAVEREADER_H
