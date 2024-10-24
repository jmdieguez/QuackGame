#ifndef COMMAND_H
#define COMMAND_H

#include "gamecontext.h"

class Command
{
private:
public:
    virtual void execute(GameContext &game_context) = 0;
    virtual void undo(GameContext &game_context) = 0;
    virtual ~Command() {}
};

#endif // COMMAND_H
