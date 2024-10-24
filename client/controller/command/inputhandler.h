#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL_events.h>
#include "moveleftcommand.h"
#include "moverightcommand.h"
#include "movebentdowncommand.h"

class InputHandler
{
private:
public:
    InputHandler();
    void execute_command(SDL_Event &event, GameContext &game_context);
    void undo_command(SDL_Event &event, GameContext &game_context);
    ~InputHandler();
};

#endif // INPUT_HANDLER_H