#include "command.h"

class Shoot : public Command
{
private:
public:
    Shoot();
    void execute(GameContext &game_context) override;
    void undo(GameContext &game_context) override;
    ~Shoot();
};