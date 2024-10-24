#ifndef MOVE_RIGHT_COMMAND_H
#define MOVE_RIGHT_COMMAND_H

#include "command.h"

class MoveRightCommand : public Command

{
private:
public:
    MoveRightCommand();
    void execute(GameContext &game_context) override;
    void undo(GameContext &game_context) override;
    ~MoveRightCommand();
};

#endif // MOVE_RIGHT_COMMAND_H