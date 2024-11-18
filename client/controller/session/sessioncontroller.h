#ifndef SESSION_CONTROLLER_H
#define SESSION_CONTROLLER_H

#include "cheatstorage.h"

#include "../command/inputhandler.h"
#include "../command/gamecontext.h"
#include "../../../common/queue.h"
#include "../../../common/snapshots.h"

class SessionController
{
private:
    CheatStorage cheat_storage;
    Queue<Snapshot> queue_receiver;
    Queue<ClientActionType> queue_sender;
    InputHandler input;
    GameContext game_context;

public:
    SessionController();
    Queue<Snapshot> &get_queue_receiver();
    void process_input(SDL_Event &event);
    void revert_command(SDL_Event &event);
    Queue<ClientActionType> &get_queue_sender();
    ~SessionController();
};

#endif // SESSION_CONTROLLER_H