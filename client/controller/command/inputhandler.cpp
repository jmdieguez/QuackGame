#include "inputhandler.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

InputHandler::InputHandler()
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
        command = &left_command;
        break;
    case SDLK_d:
        command = &right_command;
        break;
    case SDLK_s:
        command = &bent_down_command;
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
        command = &left_command;
        break;
    case SDLK_d:
        command = &right_command;
        break;
    case SDLK_s:
        command = &bent_down_command;
        break;
    }
    command->undo(game_context);
}

InputHandler::~InputHandler()
{
}
