#include "JSONSaveReader.h"

std::vector<Block> JSONSaveReader::getPiecesOnBoard()
{
    std::vector<Block> onBoard;
    const rapidjson::Value& piecesOnBoard = document["piecesOnBoard"];
    for (rapidjson::SizeType i = 0; i < piecesOnBoard.Size(); ++i)
    {
        const rapidjson::Value &tmp = piecesOnBoard[i];
        PieceType pieceType = tableOfTypes.at(tmp["type"].GetString());
        Player player = tableOfPlayers.at(tmp["player"].GetString());
        Position position = Position(tmp["position"][0].GetInt(),tmp["position"][1].GetInt());
        onBoard.push_back(Block(pieceType, player, position));
    }
    return onBoard;
}

std::vector<PieceType> JSONSaveReader::getCapturedPieces(Player player)
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
    const rapidjson::Value &tmp = document["capturedPieces"][sPlayer.c_str()];
    for (rapidjson::SizeType i = 0; i < tmp.Size(); ++i)
    {
        captured.push_back(tableOfTypes.at(tmp[i]["type"].GetString()));
    }
    return captured;
}



