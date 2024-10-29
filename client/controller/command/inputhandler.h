#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL_events.h>
#include "moveleftcommand.h"
#include "moverightcommand.h"
#include "movebentdowncommand.h"
#include "../../../common/client_actions.h"

class InputHandler
{
private:
    Queue<ClientActionType> &queue_sender;
    MoveLeftCommand left_command;
    MoveRightCommand right_command;
    MoveBentDownCommand bent_down_command;

    Command *get_command(SDL_Keycode key);

public:
    InputHandler(Queue<ClientActionType> &queue_sender);
    void execute_command(SDL_Event &event, GameContext &game_context);
    void undo_command(SDL_Event &event, GameContext &game_context);
    ~InputHandler();
};

#endif // INPUT_HANDLER_H