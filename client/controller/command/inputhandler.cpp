#include "inputhandler.h"

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

Command *InputHandler::get_command(SDL_Keycode key)
{
    switch (key)
    {
    case SDLK_a:
        return &left_command;
    case SDLK_d:
        return &right_command;
    case SDLK_s:
        return &bent_down_command;
    default:
        return nullptr;
    }
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

InputHandler::InputHandler(Queue<ClientActionType> &queue_sender) : queue_sender(queue_sender)
{
}

void InputHandler::execute_command(SDL_Event &event, GameContext &game_context)
{
    Command *command = get_command(event.key.keysym.sym);
    if (!command)
        return;
    command->execute(game_context);
}

void InputHandler::undo_command(SDL_Event &event, GameContext &game_context)
{
    Command *command = get_command(event.key.keysym.sym);
    if (!command)
        return;
    command->undo(game_context);
}

InputHandler::~InputHandler()
{
}
