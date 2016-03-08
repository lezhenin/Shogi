#include "Command.h"

Command::Command()
{

}

Command::~Command()
{
    delete this->logic;
}

