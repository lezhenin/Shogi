#ifndef SHOGI_GAME_H
#define SHOGI_GAME_H
#include "../../ShogiCore/ShogiGameAPI.h"
#include "Scene.h"

class Game : public Scene
{

public:

    Game();

    virtual void show();
    virtual ~Game();

private:
    void input();
    void stop();
    void print();
    void printMessages(ListOfGameSituations &list);
    void printBoard(AbstractBoard &board);
    void printListOfCapturedPieces(Player player);

    ShogiGameAPI *game;
    bool isRun = false;

    std::map<std::string,int> tableOfCommands = {{"pick",0},{"unpick",1},{"move",2},{"drop",3},{"exit",4},{"show", 5},{"undo", 6}, {"redo", 7}};
    std::map<std::string,PieceType> tableOfTypes = {{"pawn", Pawn},{"king", King}, {"golden general", GoldGeneral}, {"rook" ,Rook},
                                                    {"bishop", Bishop}, {"silver general", SilverGeneral}, {"knight", Knight}, {"lance", Lance}};
    std::map<PieceType,std::string> tableOfLabels = {{King, "uK"}, {GoldGeneral, "uG"}, {Rook, "uR"}, {Bishop, "uB"}, {SilverGeneral, "uS"}, {Knight, "uH"}, {Lance, "uL"}, {Pawn, "uP"},
                                                     {PromotedRook, "pR"}, {PromotedBishop, "pB"}, {PromotedSilverGeneral, "pS"}, {PromotedKnight, "pH"}, {PromotedLance, "pL"}, {PromotedPawn, "pP"}};
    std::map<Player,std::string> tableOfPlayers = {{Sente, "Sente"},{Gote, "Gote"}};

};


#endif //SHOGI_GAME_H