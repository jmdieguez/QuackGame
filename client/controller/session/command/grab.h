#include "command.h"

class Grab : public Command
{
private:
public:
    Grab();
    void execute(GameContext &game_context) override;
    void undo(GameContext &game_context) override;
    ~Grab();
};