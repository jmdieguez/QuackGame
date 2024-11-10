#ifndef MOVE_BENT_DOWN_H
#define MOVE_BENT_DOWN_H

#include "command.h"

class MoveBentDown : public Command
{
private:
public:
    MoveBentDown();
    void execute(GameContext &game_context) override;
    void undo(GameContext &game_context) override;
    ~MoveBentDown();
};

#endif // MOVE_BENT_DOWN_H
