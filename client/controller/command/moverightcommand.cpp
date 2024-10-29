#include "moverightcommand.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

MoveRightCommand::MoveRightCommand()
{
}

void MoveRightCommand::execute(GameContext &game_context)
{
    game_context.set_opposite_direction_active(true);
    game_context.push_message(ClientActionType::MOVE_RIGHT);
}

void MoveRightCommand::undo(GameContext &game_context)
{
    if (!game_context.is_opposite_direction_pressed())
        return;
    game_context.set_opposite_direction_active(false);
    std::cout << "Envie el mensaje para que se pare en derecha" << std::endl;
    game_context.push_message(ClientActionType::STOP_MOVING_RIGHT);
}

MoveRightCommand::~MoveRightCommand()
{
}
