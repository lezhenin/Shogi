#ifndef SHOGI_ACTION_H
#define SHOGI_ACTION_H


class Action
{
public:

    virtual void execute() = 0;
    virtual void unExecute() = 0;

    virtual ~Action() { }
};


#endif //SHOGI_ACTION_H
