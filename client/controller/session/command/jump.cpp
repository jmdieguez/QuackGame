#include "jump.h"

Jump::Jump()
{
}

void Jump::execute(GameContext &game_context)
{
    if (game_context.is_jumping)
        return;
    game_context.is_jumping = true;
    game_context.push_message(ClientActionType::JUMP);
}

void Jump::undo(GameContext &game_context)
{
    game_context.is_jumping = false;
    game_context.push_message(ClientActionType::STOP_JUMPING);
}

Jump::~Jump()
{
}
