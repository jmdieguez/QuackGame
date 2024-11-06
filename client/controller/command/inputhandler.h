#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL_events.h>
#include "moveleft.h"
#include "moveright.h"
#include "movebentdown.h"
#include "shoot.h"
#include "../../../common/client_actions.h"

class InputHandler
{
private:
    Queue<ClientActionType> &queue_sender;
    MoveLeft left;
    MoveRight right;
    MoveBentDown bent_down;
    Shoot shoot;

    Command *get_command(SDL_Keycode key);

public:
    InputHandler(Queue<ClientActionType> &queue_sender);
    void execute_command(SDL_Event &event, GameContext &game_context);
    void undo_command(SDL_Event &event, GameContext &game_context);
    ~InputHandler();
};

#endif // INPUT_HANDLER_H