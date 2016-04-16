#ifndef SHOGI_GAME_H
#define SHOGI_GAME_H
#include "../../ShogiCore/API/ShogiGameAPI.h"
#include "Scene.h"

/**
 * @brief Сцена, содержащая игровой процесс.
 */
class Game : public Scene
{

public:

    explicit Game(bool newGame = true);

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
    void printBoard(AbstractBoard &board) const;

    /**
     * @brief Распечатать список захваченных фигур.
     *
     * @param player Игрок, чьи фигуры будут
     * выведены на экран
     */
    void printListOfCapturedPieces(const Player &player) const;

    bool checkPosition(int horizontal, int vertical) const;

    bool pick() const;
    bool unpick() const;
    bool move() const;
    bool drop() const;
    bool undo() const;
    bool redo() const;
    bool save() const;
    bool load() const;

    int countPieces(const PieceType pieceType, const Player &player, const ListOfPieces &pieces) const;

    ShogiGameAPI *game;
    bool isRun = false;

    const std::map<std::string,int> tableOfCommands =
        {
            {  "pick", 0},
            {"unpick", 1},
            {  "move", 2},
            {  "drop", 3},
            {  "exit", 4},
            {  "show", 5},
            {  "undo", 6},
            {  "redo", 7},
            {  "save", 8},
            {  "load", 9}
        };

    const std::map<std::string,PieceType> tableOfTypes =
        {
            {          "pawn",          Pawn},
            {          "king",          King},
            {"golden general",   GoldGeneral},
            {          "rook",          Rook},
            {        "bishop",        Bishop},
            {"silver general", SilverGeneral},
            {        "knight",        Knight},
            {         "lance",         Lance}
        };

    const std::map<PieceType,std::string> tableOfLabels =
        {
            {                 King, "nK"},
            {          GoldGeneral, "nG"},
            {                 Rook, "nR"},
            {               Bishop, "nB"},
            {        SilverGeneral, "nS"},
            {               Knight, "nH"},
            {                Lance, "nL"},
            {                 Pawn, "nP"},
            {         PromotedRook, "pR"},
            {       PromotedBishop, "pB"},
            {PromotedSilverGeneral, "pS"},
            {       PromotedKnight, "pH"},
            {        PromotedLance, "pL"},
            {         PromotedPawn, "pP"}};

    const std::map<Player,std::string> tableOfPlayers =
        {
            {Sente, "Sente"},
            { Gote,  "Gote"}
        };
};


#endif //SHOGI_GAME_H
