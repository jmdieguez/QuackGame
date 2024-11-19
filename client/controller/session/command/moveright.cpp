#include "moveright.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

MoveRight::MoveRight()
{
}

void MoveRight::execute(GameContext &game_context)
{
    if (game_context.right_direction || game_context.is_bent_down)
        return;
    game_context.right_direction = true;
    game_context.push_message(ClientActionType::MOVE_RIGHT);
}

void MoveRight::undo(GameContext &game_context)
{
    game_context.right_direction = false;
    if (game_context.left_direction)
        return;
    game_context.push_message(ClientActionType::STOP_MOVING_RIGHT);
}

MoveRight::~MoveRight()
{
}