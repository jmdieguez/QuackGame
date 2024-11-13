#include "moveleft.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

MoveLeft::MoveLeft()
{
}

void MoveLeft::execute(GameContext &game_context)
{
    if (game_context.is_left_direction_pressed() || game_context.is_bent_down_pressed())
        return;
    game_context.set_left_direction_active(true);
    game_context.push_message(ClientActionType::MOVE_LEFT);
}

void MoveLeft::undo(GameContext &game_context)
{
    game_context.set_left_direction_active(false);
    if (game_context.is_right_direction_pressed())
        return;
    game_context.push_message(ClientActionType::STOP_MOVING_LEFT);
}

MoveLeft::~MoveLeft()
{
}