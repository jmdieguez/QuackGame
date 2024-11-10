#include "moveright.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

MoveRight::MoveRight()
{
}

void MoveRight::execute(GameContext &game_context)
{
    if (game_context.is_right_direction_pressed() || game_context.is_bent_down_pressed())
        return;
    game_context.set_right_direction_active(true);
    game_context.push_message(ClientActionType::MOVE_RIGHT);
}

void MoveRight::undo(GameContext &game_context)
{
    game_context.set_right_direction_active(false);
    if (game_context.is_left_direction_pressed())
        return;
    game_context.push_message(ClientActionType::STOP_MOVING_RIGHT);
}

MoveRight::~MoveRight()
{
}
