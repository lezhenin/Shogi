#ifndef GAMECORE_H
#define GAMECORE_H
#include "Board.h"
#include "enumirations.h"
#include "Position.h"


/// Игровой интерфес
class ShogiAPI
{

public:

   ///Метод инициализирующий игру
   virtual void initGame()=0;
   ///Метод, позволяющий выбрать фигуры на доске
   virtual void pickPiece(const Position& position)=0;
   ///Метод, позволяющий переместить фигуру на доске
   virtual void movePiece(const Position& position)=0;
   ///Метод, позволяющий превернуть фигуру на доске
   virtual void promotePiece(const Position& position)=0;
   ///Метод, позволяющий поставить фигуру из захваченных на доску
   virtual void dropPiece(const PieceType pt, const Position& position)=0;
   ///Метод, позволяющий указатель на игровую модель доски
   virtual Board &getBoard()=0;
   ///Метод, позволяющий получить состояние текущей игоровой ситуации
   virtual void getGameStatus()=0;
};

#endif // GAMECORE_H
