#ifndef GAMECORE_H
#define GAMECORE_H


class GameAPI
{

public:
   virtual GameAPI();
   virtual void pickPiece();
   virtual void movePiece();
   virtual void getBoard();
};

#endif // GAMECORE_H
