#include "JSONSaveManager.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

using namespace shogi;

std::vector<Block> JSONSaveManager::getPiecesOnBoard() noexcept
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

std::vector<PieceType> JSONSaveManager::getCapturedPieces(const Player &player) noexcept
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

void JSONSaveManager::addPieceOnBoard(const PieceType pieceType, const Player &player, const Position &position) noexcept
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

void JSONSaveManager::addCapturedPiece(const Player &player, const PieceType pieceType) noexcept
{
    rapidjson::Value tmp;
    tmp.SetObject();
    tmp.AddMember("type",rapidjson::Value(rapidjson::kStringType),save.GetAllocator());
    tmp["type"].SetString(tableOfTypes.at(pieceType).c_str(),tableOfTypes.at(pieceType).size());
    save["capturedPieces"][tableOfPlayers.at(player).c_str()].PushBack(tmp,save.GetAllocator());
}

const std::string JSONSaveManager::getJSONString() const noexcept
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    save.Accept(writer);
    return buffer.GetString();
}

JSONSaveManager::JSONSaveManager() noexcept
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
    const char *string = JSONString.c_str();
    rapidjson::ParseResult result;
    result = save.Parse(string);
    if(result.Code() != rapidjson::kParseErrorNone)
    {
        throw std::exception();
    }
}

void JSONSaveManager::clear() noexcept
{
    save.Clear();
}

Player &JSONSaveManager::getCurrentPlayer() noexcept
{

    return reverseTableOfPlayers.at(save["currentPlayer"].GetString());
}

void JSONSaveManager::setCurrentPlayer(const Player &player) noexcept
{
    save["currentPlayer"].SetString(tableOfPlayers.at(player).c_str(),tableOfPlayers.at(player).size());
}

