#include "movebentdowncommand.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

MoveBentDownCommand::MoveBentDownCommand()
{
}

void MoveBentDownCommand::execute(GameContext &game_context)
{
    game_context.push_message(ClientActionType::LAY);
}

void MoveBentDownCommand::undo(GameContext &game_context)
{
    game_context.push_message(ClientActionType::STAND_UP);
}

MoveBentDownCommand::~MoveBentDownCommand()
{
}
