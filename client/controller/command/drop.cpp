#include "drop.h"

Drop::Drop()
{
}

void Drop::execute(GameContext &game_context)
{
    if (game_context.is_droping)
        return;
    game_context.is_droping = true;
    game_context.push_message(ClientActionType::DROP);
}

void Drop::undo(GameContext &game_context)
{
    game_context.is_droping = false;
}

Drop::~Drop()
{
}
