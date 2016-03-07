#ifndef GAMECORE_H
#define GAMECORE_H
#include "Position.h"


/// Игровой интерфес
class GameAPI
{

public:

   virtual void initGame()=0;
   virtual void pickPiece(Position& position)=0;
   virtual void movePiece(Position& position)=0;
   virtual void promotePiece(Position& position)=0;
   virtual void dropPiece()=0;
   virtual void getBoard()=0;
   virtual void getGameStatus()=0;
};

#endif // GAMECORE_H
