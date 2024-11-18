#include "command.h"

class Jump : public Command
{
private:
public:
    Jump();
    void execute(GameContext &game_context) override;
    void undo(GameContext &game_context) override;
    ~Jump();
};
