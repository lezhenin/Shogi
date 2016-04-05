#ifndef SHOGI_GAME_H
#define SHOGI_GAME_H


#include "../ShogiCore/Shogi.h"
#include "Commands/Command.h"

class ConsoleGame
{
public:

    ConsoleGame();
    void start();
    void stop();
    virtual ~ConsoleGame();

private:
    Command *inputCommand();
   // void pirintMessages();
    void printBoard(AbstractBoard *board);

    ShogiGameAPI *game;
    bool isRun = false;

    std::map<std::string,int> tableOfCommands = {{"pick",0},{"unpick",1},{"move",2},{"drop",3},{"exit",4}};
    std::map<std::string,PieceType> tableOfTypes = {{"pawn", Pawn},{"king", King}, {"golden general", GoldGeneral}, {"rook" ,Rook},
                                                    {"bishop", Bishop}, {"silver general", SilverGeneral}, {"knight", Knight}, {"lance", Lance}};
    std::map<PieceType,std::string> tableOfLabels = {{King, "uK"}, {GoldGeneral, "uG"}, {Rook, "uR"}, {Bishop, "uB"}, {SilverGeneral, "uS"}, {Knight, "uH"}, {Lance, "uL"}, {Pawn, "uP"},
                                       {PromotedRook, "pR"}, {PromotedBishop, "pB"}, {PromotedSilverGeneral, "pS"}, {PromotedKnight, "pH"}, {PromotedLance, "pL"}, {PromotedPawn, "pP"}};
};

#endif //SHOGI_GAME_H