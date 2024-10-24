#ifndef MOVE_LEFT_COMMAND_H
#define MOVE_LEFT_COMMAND_H

#include "command.h"

class MoveLeftCommand : public Command
{
private:
public:
    MoveLeftCommand();
    void execute(GameContext &game_context) override;
    void undo(GameContext &game_context) override;
    ~MoveLeftCommand();
};

#endif // MOVE_LEFT_COMMAND_H
