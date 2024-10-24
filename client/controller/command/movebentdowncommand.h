#ifndef MOVE_BENT_DOWN_COMMAND_H
#define MOVE_BENT_DOWN_COMMAND_H

#include "command.h"

class MoveBentDownCommand : public Command
{
private:
public:
    MoveBentDownCommand();
    void execute(GameContext &game_context) override;
    void undo(GameContext &game_context) override;
    ~MoveBentDownCommand();
};

#endif // MOVE_BENT_DOWN_COMMAND_H
