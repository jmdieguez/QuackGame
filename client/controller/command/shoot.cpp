#include "shoot.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Shoot::Shoot()
{
}

void Shoot::execute(GameContext &game_context)
{
    game_context.push_message(ClientActionType::SHOOT);
}

void Shoot::undo(GameContext &game_context)
{
    game_context.push_message(ClientActionType::STOP_SHOOTING);
}

Shoot::~Shoot()
{
}
