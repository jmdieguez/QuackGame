#include "movebentdowncommand.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

MoveBentDownCommand::MoveBentDownCommand()
{
}

void MoveBentDownCommand::execute(GameContext &game_context)
{
    if (game_context.is_bent_down_pressed())
        return;
    game_context.set_bent_down_active(true);
    game_context.push_message(ClientActionType::LAY);
}

void MoveBentDownCommand::undo(GameContext &game_context)
{
    game_context.set_bent_down_active(false);
    game_context.push_message(ClientActionType::STAND_UP);
}

MoveBentDownCommand::~MoveBentDownCommand()
{
}
