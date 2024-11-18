#include "moveleft.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

MoveLeft::MoveLeft()
{
}

void MoveLeft::execute(GameContext &game_context)
{
    if (game_context.left_direction || game_context.is_bent_down)
        return;
    game_context.left_direction = true;
    game_context.push_message(ClientActionType::MOVE_LEFT);
}

void MoveLeft::undo(GameContext &game_context)
{
    game_context.left_direction = false;
    if (game_context.right_direction)
        return;
    game_context.push_message(ClientActionType::STOP_MOVING_LEFT);
}

MoveLeft::~MoveLeft()
{
}
