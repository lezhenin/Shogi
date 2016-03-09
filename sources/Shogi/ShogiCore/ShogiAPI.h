#ifndef GAMECORE_H
#define GAMECORE_H
#include "Board.h"
#include "enumirations.h"
#include "Position.h"


/// Игровой интерфес
class ShogiAPI
{

public:

   virtual void initGame()=0;
   virtual void pickPiece(Position& position)=0;
   virtual void movePiece(Position& position)=0;
   virtual void promotePiece(Position& position)=0;
   virtual void dropPiece(PieceType pt)=0;
   virtual Board &getBoard()=0;
   virtual void getGameStatus()=0;
};

#endif // GAMECORE_H
