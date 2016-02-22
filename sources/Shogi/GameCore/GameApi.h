#ifndef GAMECORE_H
#define GAMECORE_H


class GameAPI
{

public:

   virtual void initGame()=0;
   virtual void pickPiece()=0;
   virtual void movePiece()=0;
   virtual void getBoard()=0;
   virtual bool isFinish()=0;
};

#endif // GAMECORE_H
