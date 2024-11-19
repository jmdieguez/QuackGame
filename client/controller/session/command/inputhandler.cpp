#include "inputhandler.h"

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

Command *InputHandler::get_command(SDL_Keycode key)
{

    std::string keyName = SDL_GetKeyName(key);
    switch (key)
    {
    case SDLK_w:
        return &look_up;
    case SDLK_a:
        return &left;
    case SDLK_d:
        return &right;
    case SDLK_s:
        return &bent_down;
    case SDLK_t:
        return &shoot;
    case SDLK_g:
        return &drop;
    case SDLK_e:
        return &grab;
    case SDLK_SPACE:
        return &jump;
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

void InputHandler::execute_command(SDL_Event &event, GameContext &game_context, CheatStorage &cheats)
{
    SDL_Keycode key = event.key.keysym.sym;
    std::string key_name = SDL_GetKeyName(key);
    cheats.add_input(key_name);
    cheats.active_cheat(queue_sender);
    Command *command = get_command(key);
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