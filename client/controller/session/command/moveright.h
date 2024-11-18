#ifndef MOVE_RIGHT_H
#define MOVE_RIGHT_H

#include "command.h"

class MoveRight : public Command

{
private:
public:
    MoveRight();
    void execute(GameContext &game_context) override;
    void undo(GameContext &game_context) override;
    ~MoveRight();
};

#endif // MOVE_RIGHT_H