#include "moverightcommand.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

MoveRightCommand::MoveRightCommand()
{
}

void MoveRightCommand::execute(GameContext &game_context)
{
    game_context.set_is_running(true);
    game_context.set_is_right_direction(true);
}

void MoveRightCommand::undo(GameContext &game_context)
{
    if (!game_context.get_is_right_direction())
        return;
    game_context.set_is_running(false);
}

MoveRightCommand::~MoveRightCommand()
{
}
