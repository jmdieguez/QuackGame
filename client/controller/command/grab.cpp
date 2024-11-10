#include "grab.h"

Grab::Grab()
{
}

void Grab::execute(GameContext &game_context)
{
    if (game_context.is_grabing_pressed())
        return;
    game_context.set_grabing_active(true);
    game_context.push_message(ClientActionType::GRAB);
}

void Grab::undo(GameContext &game_context)
{
    game_context.set_grabing_active(false);
}

Grab::~Grab()
{
}
