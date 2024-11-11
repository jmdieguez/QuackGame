#include "jump.h"

Jump::Jump()
{
}

void Jump::execute(GameContext &game_context)
{
    if (game_context.is_jumping_pressed())
        return;
    game_context.set_jumping_active(true);
    game_context.push_message(ClientActionType::JUMP);
}

void Jump::undo(GameContext &game_context)
{
    game_context.set_jumping_active(false);
    game_context.push_message(ClientActionType::STOP_JUMPING);
}

Jump::~Jump()
{
}
