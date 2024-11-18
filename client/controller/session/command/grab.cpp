#include "grab.h"

Grab::Grab()
{
}

void Grab::execute(GameContext &game_context)
{
    if (game_context.is_grabing)
        return;
    game_context.is_grabing = true;
    game_context.push_message(ClientActionType::GRAB);
}

void Grab::undo(GameContext &game_context)
{
    game_context.is_grabing = false;
}

Grab::~Grab()
{
}
