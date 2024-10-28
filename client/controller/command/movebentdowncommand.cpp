#include "movebentdowncommand.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

MoveBentDownCommand::MoveBentDownCommand()
{
}

void MoveBentDownCommand::execute(GameContext &game_context)
{
    game_context.push_message(ClientActionType::MOVE_LEFT);
}

void MoveBentDownCommand::undo(GameContext &game_context)
{
    game_context.push_message(ClientActionType::STOP_MOVING_LEFT);
}

MoveBentDownCommand::~MoveBentDownCommand()
{
}
