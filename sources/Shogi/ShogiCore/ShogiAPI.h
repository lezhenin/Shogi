#ifndef GAMECORE_H
#define GAMECORE_H

/// Игровой интерфес
class GameAPI
{

public:

   virtual void initGame()=0;
   virtual void pickPiece()=0; 
   virtual void movePiece()=0;
   virtual void promotePiece()=0;
   virtual void dropPiece()=0;
   virtual void getBoard()=0;
   virtual void getGameStatus()=0;
};

#endif // GAMECORE_H
