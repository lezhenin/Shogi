#ifndef SHOGI_GAME_H
#define SHOGI_GAME_H
#include "../../ShogiCore/ShogiGameAPI.h"
#include "Scene.h"

/**
 * @brief Сцена, содержащая игровой процесс.
 */
class Game : public Scene
{

public:

    Game();

    virtual void show();
    virtual ~Game();

private:
    /**
     * @brief Ввод
     *
     * Метод обрабатывает входную команду.
     */
    void input();

    /**
     * @brief Остновить
     *
     * Останавливает игровой цикл
     */
    void stop();

    /**
     * @brief Отрисовать
     *
     * Распечатывает доску и обрабатывает полученные
     * сообщения
     */
    void print();

    /**
     * @brief Распечатать сообщения
     *
     * Распечатывает и обрабатывает сообщения
     */
    void printMessages(ListOfGameSituations &list);

    /**
     * @brief Распечатать доску
     *
     * Отрисовывает доску в консоли
     */
    //TODO: это не может быть const?
    void printBoard(AbstractBoard &board);

    /**
     * @brief Распечатать список захваченных фигур.
     *
     * @param player Игрок, чьи фигуры будут
     * выведены на экран
     */
        //TODO: это не может быть const?
    void printListOfCapturedPieces(Player player);

    ShogiGameAPI *game;
    bool isRun = false;

    //TODO: у меня экран в ноутбуке 13 дюймов, нормальный экран, а ничего не разобрать было при старом форматировании
    std::map<std::string,int> tableOfCommands =
        {
            {"pick",0},
            {"unpick",1},
            {"move",2},
            {"drop",3},
            {"exit",4},
            {"show", 5},
            {"undo", 6},
            {"redo", 7}
        };

    std::map<std::string,PieceType> tableOfTypes =
        {
            {"pawn", Pawn},
            {"king", King},
            {"golden general", GoldGeneral},
            {"rook" ,Rook},
            {"bishop", Bishop},
            {"silver general", SilverGeneral},
            {"knight", Knight}, {"lance", Lance}
        };

    std::map<PieceType,std::string> tableOfLabels =
        {
            {King, "uK"},
            {GoldGeneral, "uG"},
            {Rook, "uR"},
            {Bishop, "uB"},
            {SilverGeneral, "uS"},
            {Knight, "uH"},
            {Lance, "uL"},
            {Pawn, "uP"},
            {PromotedRook, "pR"},
            {PromotedBishop, "pB"},
            {PromotedSilverGeneral, "pS"},
            {PromotedKnight, "pH"},
            {PromotedLance, "pL"},
            {PromotedPawn, "pP"}};

    std::map<Player,std::string> tableOfPlayers =
        {
            {Sente, "Sente"},
            {Gote, "Gote"}
        };
};


#endif //SHOGI_GAME_H
