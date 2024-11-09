#include "drop.h"

Drop::Drop()
{
}

void Drop::execute(GameContext &game_context)
{
    if (game_context.is_droping_pressed())
        return;
    game_context.set_droping_active(true);
    game_context.push_message(ClientActionType::DROP);
}

void Drop::undo(GameContext &game_context)
{
    game_context.set_droping_active(false);
}

Drop::~Drop()
{
}
