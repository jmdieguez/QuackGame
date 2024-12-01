#include "inputhandler.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

InputHandler::InputHandler(Queue<ClientIdAction> &queue_sender, const PlayerKeyConfig &key_config) : queue_sender(queue_sender),
                                                                                                     game_context(id, queue_sender),
                                                                                                     key_config(key_config)
{
}

void InputHandler::execute_command(SDL_Event &event, CheatStorage &cheats)
{
    if (event.type == SDL_KEYDOWN)
    {
        Command *command = key_config.get_command(event.key.keysym.sym);
        if (command)
            command->execute(game_context);
    }
}

void InputHandler::undo_command(SDL_Event &event)
{
    if (event.type == SDL_KEYUP)
    {
        Command *command = key_config.get_command(event.key.keysym.sym);
        if (command)
            command->undo(game_context);
    }
}

void InputHandler::set_id(uint16_t new_id)
{
    id = new_id;
}

InputHandler::~InputHandler() {}
