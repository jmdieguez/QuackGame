#include "shoot.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Shoot::Shoot()
{
}

void Shoot::execute(GameContext &game_context)
{
    if (game_context.is_shooting_pressed())
        return;
    game_context.set_shooting_active(true);
    game_context.push_message(ClientActionType::SHOOT);
}

void Shoot::undo(GameContext &game_context)
{
    game_context.push_message(ClientActionType::STOP_SHOOTING);
    game_context.set_shooting_active(false);
}

Shoot::~Shoot()
{
}
