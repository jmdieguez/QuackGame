#include "moveleft.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

MoveLeft::MoveLeft()
{
}

void MoveLeft::execute(GameContext &game_context)
{
    game_context.push_message(ClientActionType::MOVE_LEFT);
}

void MoveLeft::undo(GameContext &game_context)
{
    game_context.push_message(ClientActionType::STOP_MOVING_LEFT);
}

MoveLeft::~MoveLeft()
{
}
