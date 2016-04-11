#include "JSONSaveWriter.h"

void JSONSaveWriter::addPieceOnBoard(PieceType pieceType, Player player, Position position)
{
    rapidjson::Value tmp;
    tmp.SetObject();
    tmp.AddMember("type", rapidjson::Value(rapidjson::kStringType), save.GetAllocator());
    tmp["type"].SetString(tableOfTypes.at(pieceType));
    tmp.AddMember("player", rapidjson::Value(rapidjson::kStringType), save.GetAllocator());
    tmp["player"].SetString(tableOfPlayers.at(player));
    tmp.AddMember("position", rapidjson::Value(rapidjson::kArrayType), save.GetAllocator());
    tmp["position"].PushBack(position.getHorizontal(), save.GetAllocator());
    tmp["position"].PushBack(position.getVertical(), save.GetAllocator());
    save["piecesOnBoard"].PushBack(tmp, save.GetAllocator());
}

JSONSaveWriter::JSONSaveWriter()
{
    save.SetObject();
    save.AddMember("piecesOnBoard",rapidjson::Value(rapidjson::kArrayType),save.GetAllocator());
    save.AddMember("capturedPieces",rapidjson::Value(rapidjson::kObjectType),save.GetAllocator());
    save["capturedPieces"].AddMember("sente",rapidjson::Value(rapidjson::kArrayType),save.GetAllocator());
    save["capturedPieces"].AddMember("gote",rapidjson::Value(rapidjson::kArrayType),save.GetAllocator());
}

void JSONSaveWriter::addCapturedPiece(Player player, PieceType pieceType)
{
    rapidjson::Value tmp;
    tmp.SetObject();
    tmp.AddMember("type",rapidjson::Value(rapidjson::kStringType),save.GetAllocator());
    tmp["type"].SetString(tableOfTypes.at(pieceType));
    save["capturedPieces"][tableOfPlayers.at(player)].PushBack(tmp,save.GetAllocator());
}


