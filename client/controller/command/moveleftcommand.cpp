#include "moveleftcommand.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

MoveLeftCommand::MoveLeftCommand()
{
}

void MoveLeftCommand::execute(GameContext &game_context)
{
    game_context.set_is_running(true);
    game_context.set_is_right_direction(false);
}

void MoveLeftCommand::undo(GameContext &game_context)
{
    if (game_context.get_is_right_direction())
        return;
    game_context.set_is_running(false);
}

MoveLeftCommand::~MoveLeftCommand()
{
}
