#include "inputhandler.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

InputHandler::InputHandler(Queue<ClientActionType>& queue_sender): queue_sender(queue_sender)
{
}

void InputHandler::execute_command(SDL_Event &event, GameContext &game_context)
{
    Command *command = nullptr;
    MoveLeftCommand left_command;
    MoveRightCommand right_command;
    MoveBentDownCommand bent_down_command;
    switch (event.key.keysym.sym)
    {
    case SDLK_a:
        queue_sender.push(ClientActionType::MOVE_LEFT);
        command = &left_command;
        break;
    case SDLK_d:
        queue_sender.push(ClientActionType::MOVE_RIGHT);
        command = &right_command;
        break;
    case SDLK_s:
        queue_sender.push(ClientActionType::LAY);
        command = &bent_down_command;
        break;
    default:
      break;
    }
    command->execute(game_context);
}

void InputHandler::undo_command(SDL_Event &event, GameContext &game_context)
{
    Command *command = nullptr;
    MoveLeftCommand left_command;
    MoveRightCommand right_command;
    MoveBentDownCommand bent_down_command;
    switch (event.key.keysym.sym)
    {
    case SDLK_a:
        queue_sender.push(ClientActionType::STOP_MOVING_LEFT);
        command = &left_command;
        break;
    case SDLK_d:
        queue_sender.push(ClientActionType::STOP_MOVING_RIGHT);
        command = &right_command;
        break;
    case SDLK_s:
        queue_sender.push(ClientActionType::STAND_UP);
        command = &bent_down_command;
        break;
    default:
        break;
    }
    command->undo(game_context);
}

InputHandler::~InputHandler()
{
}
