#ifndef PIECE_H
#define PIECE_H
#include "Square.h"

class Square;

const int PROMOTION_STEP = 10;

enum Player{
    Sente=0, Gote
};
/**
 * /enum PieceType
 * Содержит типы сущестсвующих фигур, включая перевернутые фигуры.
 */
enum PieceType{
    King=2, GoldGeneral, Rook, Bishop, SilverGeneral, Knight, Lance, Pawn,
    PromotedRook=Rook+PROMOTION_STEP, PromotedBishop, PromotedSilverGeneral,  PromotedKnight, PromotedLance, PromotedPawn,
};

///Модель фигуры
class Piece
{
public:

    ///Конструктор
    Piece(PieceType pt, Player pl, Square *sq=nullptr);

    ///Метод, позволяющий получить тип фигуры
    PieceType getType() const;
    ///Метод, позволяющий получить игрока (сторону), которому принадлежит фигура
    Player getPlayer() const;
    ///Метод, позволяющий получить позицию фигуры
    Position &getPosition() const;
    ///Метод, позволяющий получить указатель на клетку, на которой наодится фигура
    Square *getSquare() const;

    ///Метод, позволяющий узнать была ли перевернута фигура
    inline bool wasPromoted() const;
    ///Метод, позволяющий узнать может ли фигура быть первернута
    inline bool canBePromoted() const;

    ///Метод, позволяющий перевернуть фигуру
    void promote();
    ///Метод, позволяющий отменить переворот фигуры
    void unPromote();

    ///Метод, позволяющий установить указатель на клетку доски, на которой находится фигура
    void setSquare(Square *sq);
    ///Метод, позволяющий установить игрока (сторону), котому принадлежит фигура
    void setPlayer(Player pl);

    ///Деструктор
    ~Piece();


private:

    PieceType ptype;
    Player player;
    Square *sq;

    bool promoted;
    bool bePromoted;

};





#endif // PIECE_H
