
#ifndef SHOGI_JSONSAVEWRITER_H
#define SHOGI_JSONSAVEWRITER_H

#include <map>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "../SaveWriter.h"

class JSONSaveWriter : public SaveWriter
{

public:

    JSONSaveWriter();

    virtual void addPieceOnBoard(PieceType pieceType, Player player, Position position);
    virtual void addCapturedPiece(Player player, PieceType pieceType);

    const std::string getJSONString() const
    {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        save.Accept(writer);
        JSONString = std::string(buffer.GetString());
        return JSONString;
    }

private:
    rapidjson::Document save;
    std::string JSONString;

    std::map<PieceType, std::string> tableOfTypes = {{Pawn, "pawn"},{King, "king"}, {GoldGeneral, "golden general"}, {Rook, "rook"},
                                                    {Bishop, "bishop"}, {SilverGeneral, "silver general"}, {Knight, "knight"}, {Lance, "lance"}};
    std::map<Player, std::string> tableOfPlayers = {{Sente, "sente"},{Gote, "gote"}};
};


#endif //SHOGI_JSONSAVEWRITER_H
