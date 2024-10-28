#include "moverightcommand.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

MoveRightCommand::MoveRightCommand()
{
}

void MoveRightCommand::execute(GameContext &game_context)
{
    game_context.push_message(ClientActionType::MOVE_RIGHT);
}

void MoveRightCommand::undo(GameContext &game_context)
{
    game_context.push_message(ClientActionType::STOP_MOVING_RIGHT);
}

MoveRightCommand::~MoveRightCommand()
{
}
