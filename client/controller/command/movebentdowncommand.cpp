#include "movebentdowncommand.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

MoveBentDownCommand::MoveBentDownCommand()
{
}

void MoveBentDownCommand::execute(GameContext &game_context)
{
    game_context.set_is_bent_down(true);
}

void MoveBentDownCommand::undo(GameContext &game_context)
{
    game_context.set_is_bent_down(false);
}

MoveBentDownCommand::~MoveBentDownCommand()
{
}
