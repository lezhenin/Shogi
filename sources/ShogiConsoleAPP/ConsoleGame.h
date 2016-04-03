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
    void printBoard(AbstractBoard *board);

    ShogiGameAPI *game;
    bool isRun = false;

    std::map<std::string,int> tableOfCommands = {{"pick",0},{"unpick",1},{"move",2},{"drop",3},{"exit",4}};
    std::map<std::string,PieceType> tableOfTypes = {{"pawn", Pawn},{"king", King}, {"golden general", GoldGeneral}, {"rook" ,Rook},
                                                    {"bishop", Bishop}, {"silver general", SilverGeneral}, {"knight", Knight}, {"lance", Lance}};
//    std::map<PieceType,std::string> = {{King, K}, {GoldGeneral, G}, {Rook, R}, {Bishop, B}, {SilverGeneral, S}, {Knight, H}, {Lance, L}, {Pawn, P}, {PromotedRook, R}, {PromotedBishop, B}, {PromotedSilverGeneral, S}, {PromotedKnight, H}, {PromotedLance, L}, {PromotedPawn, P}}
};

#endif //SHOGI_GAME_H
