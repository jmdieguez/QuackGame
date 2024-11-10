#include "command.h"

class LookingUp : public Command
{
private:
public:
    LookingUp();
    void execute(GameContext &game_context) override;
    void undo(GameContext &game_context) override;
    ~LookingUp();
};
