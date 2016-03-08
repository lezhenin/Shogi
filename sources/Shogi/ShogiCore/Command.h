#ifndef COMMAND_H
#define COMMAND_H
#include"ShogiGameLogic.h"

class Command
{
public:

    Command();

    virtual void execute();

    void setGameLogicClass(ShogiGameLogic *l);

    ~Command();
private:
    ShogiGameLogic *logic;
};

#endif // COMMAND_H
