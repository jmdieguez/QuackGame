#include "moveleftcommand.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

MoveLeftCommand::MoveLeftCommand()
{
}

void MoveLeftCommand::execute(GameContext &game_context)
{
    game_context.set_opposite_direction_active(false);
    game_context.push_message(ClientActionType::MOVE_LEFT);
}

void MoveLeftCommand::undo(GameContext &game_context)
{
    if (game_context.is_opposite_direction_pressed())
        return;
    game_context.set_opposite_direction_active(false);
    std::cout << "Envie el mensaje para que se pare en izquierda" << std::endl;
    game_context.push_message(ClientActionType::STOP_MOVING_LEFT);
}

MoveLeftCommand::~MoveLeftCommand()
{
}
