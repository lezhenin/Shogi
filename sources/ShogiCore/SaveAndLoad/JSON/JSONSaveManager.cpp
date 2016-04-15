
#include "JSONSaveManager.h"

std::vector<Block> JSONSaveManager::getPiecesOnBoard()
{
    std::vector<Block> onBoard;
    const rapidjson::Value& piecesOnBoard = save["piecesOnBoard"];
    for (rapidjson::SizeType i = 0; i < piecesOnBoard.Size(); ++i)
    {
        const rapidjson::Value &tmp = piecesOnBoard[i];
        PieceType pieceType = reverseTableOfTypes.at(tmp["type"].GetString());
        Player player = reverseTableOfPlayers.at(tmp["player"].GetString());
        Position position = Position(tmp["position"][0].GetInt(),tmp["position"][1].GetInt());
        onBoard.push_back(Block(pieceType, player, position));
    }
    return onBoard;
}

std::vector<PieceType> JSONSaveManager::getCapturedPieces(const Player player)
{
    std::string sPlayer;
    std::vector<PieceType> captured;
    if(player == Sente)
    {
        sPlayer = "sente";
    }
    else
    {
        sPlayer = "gote";
    }
    const rapidjson::Value &tmp = save["capturedPieces"][sPlayer.c_str()];
    for (rapidjson::SizeType i = 0; i < tmp.Size(); ++i)
    {
        captured.push_back(reverseTableOfTypes.at(tmp[i]["type"].GetString()));
    }
    return captured;
}

void JSONSaveManager::addPieceOnBoard(const PieceType pieceType, const Player player, const Position &position)
{
    rapidjson::Value tmp;
    tmp.SetObject();
    tmp.AddMember("type", rapidjson::Value(rapidjson::kStringType), save.GetAllocator());
    tmp["type"].SetString(tableOfTypes.at(pieceType).c_str(),tableOfTypes.at(pieceType).size());
    tmp.AddMember("player", rapidjson::Value(rapidjson::kStringType), save.GetAllocator());
    tmp["player"].SetString(tableOfPlayers.at(player).c_str(),tableOfPlayers.at(player).size());
    tmp.AddMember("position", rapidjson::Value(rapidjson::kArrayType), save.GetAllocator());
    tmp["position"].PushBack(position.getHorizontal(), save.GetAllocator());
    tmp["position"].PushBack(position.getVertical(), save.GetAllocator());
    save["piecesOnBoard"].PushBack(tmp, save.GetAllocator());
}

void JSONSaveManager::addCapturedPiece(const Player player, const PieceType pieceType)
{
    rapidjson::Value tmp;
    tmp.SetObject();
    tmp.AddMember("type",rapidjson::Value(rapidjson::kStringType),save.GetAllocator());
    tmp["type"].SetString(tableOfTypes.at(pieceType).c_str(),tableOfTypes.at(pieceType).size());
    save["capturedPieces"][tableOfPlayers.at(player).c_str()].PushBack(tmp,save.GetAllocator());
}

const std::string JSONSaveManager::getJSONString() const
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    save.Accept(writer);
    return buffer.GetString();
}

JSONSaveManager::JSONSaveManager()
{
    save.SetObject();
    save.AddMember("currentPlayer",rapidjson::Value(rapidjson::kStringType),save.GetAllocator());
    save.AddMember("piecesOnBoard",rapidjson::Value(rapidjson::kArrayType),save.GetAllocator());
    save.AddMember("capturedPieces",rapidjson::Value(rapidjson::kObjectType),save.GetAllocator());
    save["capturedPieces"].AddMember("sente",rapidjson::Value(rapidjson::kArrayType),save.GetAllocator());
    save["capturedPieces"].AddMember("gote",rapidjson::Value(rapidjson::kArrayType),save.GetAllocator());
}

JSONSaveManager::JSONSaveManager(const std::string &JSONString)
{
    save.Parse(JSONString.c_str());
}

void JSONSaveManager::clear()
{
    save.Clear();
}

Player JSONSaveManager::getCurrentPlayer()
{
    return reverseTableOfPlayers.at(save["currentPlayer"].GetString());
}

void JSONSaveManager::setCurrentPlayer(const Player player)
{
    save["currentPlayer"].SetString(tableOfPlayers.at(player).c_str(),tableOfPlayers.at(player).size());
}



















