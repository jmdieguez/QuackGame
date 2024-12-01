#include "inputhandler.h"

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

void InputHandler::process_cheat(SDL_Event &event, CheatStorage &cheats)
{
    std::string key_name = SDL_GetKeyName(event.key.keysym.sym);
    cheats.add_input(key_name);
    cheats.active_cheat(game_context);
}

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
    if (event.type != SDL_KEYDOWN)
        return;
    process_cheat(event, cheats);
    Command *command = key_config.get_command(event.key.keysym.sym);
    if (!command)
        return;
    command->execute(game_context);
}

void InputHandler::undo_command(SDL_Event &event)
{
    if (event.type != SDL_KEYUP)
        return;
    Command *command = key_config.get_command(event.key.keysym.sym);
    if (!command)
        return;
    command->undo(game_context);
}

void InputHandler::set_id(uint16_t new_id)
{
    id = new_id;
}

InputHandler::~InputHandler() {}
