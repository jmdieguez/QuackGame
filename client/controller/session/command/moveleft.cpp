#include "moveleft.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

MoveLeft::MoveLeft()
{
}

void MoveLeft::execute(GameContext &game_context)
{
    if (game_context.left_direction)
        return;
    if (game_context.right_direction)
    {
        game_context.right_direction = false;
        game_context.push_message(ClientActionType::STOP_MOVING_RIGHT);
    }
    game_context.left_direction = true;
    game_context.push_message(ClientActionType::MOVE_LEFT);
}

void MoveLeft::undo(GameContext &game_context)
{
    game_context.left_direction = false;
    if (!game_context.right_direction)
        game_context.push_message(ClientActionType::STOP_MOVING_LEFT);
}
MoveLeft::~MoveLeft()
{
}
