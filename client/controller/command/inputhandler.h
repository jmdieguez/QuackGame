#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL_events.h>
#include "moveleft.h"
#include "moveright.h"
#include "movebentdown.h"
#include "shoot.h"
#include "drop.h"
#include "grab.h"
#include "lookingup.h"
#include "jump.h"
#include "../../../common/client_actions.h"

class InputHandler
{
private:
    Queue<ClientActionType> &queue_sender;
    LookingUp look_up;
    MoveLeft left;
    MoveRight right;
    MoveBentDown bent_down;
    Shoot shoot;
    Drop drop;
    Grab grab;
    Jump jump;
    Command *get_command(SDL_Keycode key);

public:
    InputHandler(Queue<ClientActionType> &queue_sender);
    void execute_command(SDL_Event &event, GameContext &game_context);
    void undo_command(SDL_Event &event, GameContext &game_context);
    ~InputHandler();
};

#endif // INPUT_HANDLER_H