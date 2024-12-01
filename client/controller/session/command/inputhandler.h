#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL_events.h>
#include <unordered_map>
#include "moveleft.h"
#include "moveright.h"
#include "movebentdown.h"
#include "shoot.h"
#include "drop.h"
#include "grab.h"
#include "lookingup.h"
#include "jump.h"
#include "playerkeyconfig.h"
#include "../cheat/cheatstorage.h"
#include "../../../../common/client_actions.h"
#include "playerkeyconfigmanager.h"

class InputHandler
{
private:
    uint16_t id;
    Queue<ClientIdAction> &queue_sender;
    GameContext game_context;
    const PlayerKeyConfig &key_config;

    void process_cheat(SDL_Event &event, CheatStorage &cheats);

public:
    InputHandler(Queue<ClientIdAction> &queue_sender, const PlayerKeyConfig &key_config);
    void execute_command(SDL_Event &event, CheatStorage &cheats);
    void undo_command(SDL_Event &event);
    void set_id(uint16_t new_id);
    ~InputHandler();
};
#endif // INPUT_HANDLER_H