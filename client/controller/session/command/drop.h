#ifndef DROP_H
#define DROP_H

#include "command.h"

class Drop : public Command
{
private:
public:
    Drop();
    void execute(GameContext &game_context) override;
    void undo(GameContext &game_context) override;
    ~Drop();
};

#endif // DROP_H