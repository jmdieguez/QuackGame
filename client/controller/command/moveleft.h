#ifndef MOVE_LEFT_H
#define MOVE_LEFT_H

#include "command.h"

class MoveLeft : public Command
{
private:
public:
    MoveLeft();
    void execute(GameContext &game_context) override;
    void undo(GameContext &game_context) override;
    ~MoveLeft();
};

#endif // MOVE_LEFT_H
