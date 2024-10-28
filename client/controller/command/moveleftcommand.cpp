#include "moveleftcommand.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

MoveLeftCommand::MoveLeftCommand()
{
}

void MoveLeftCommand::execute(GameContext &game_context)
{
    game_context.push_message(ClientActionType::MOVE_LEFT);
}

void MoveLeftCommand::undo(GameContext &game_context)
{
    game_context.push_message(ClientActionType::STOP_MOVING_LEFT);
}

MoveLeftCommand::~MoveLeftCommand()
{
}
