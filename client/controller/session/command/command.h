#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include "gamecontext.h"
#include "../../common/client_actions.h"

class Command
{
private:
public:
    virtual void execute(GameContext &game_context) = 0;
    virtual void undo(GameContext &game_context) = 0;
    virtual ~Command() {}
};

#endif // COMMAND_H
