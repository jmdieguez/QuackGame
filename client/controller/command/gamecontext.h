#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include "../common/queue.h"
#include "../common/client_actions.h"

class GameContext
{
private:
    bool is_right_direction;
    bool is_running;
    bool is_bent_down;
    Queue<ClientActionType> &queue_sender;

public:
    explicit GameContext(Queue<ClientActionType> &queue_sender);
    void push_message(ClientActionType action);
    ~GameContext();
};

#endif // GAME_CONTEXT_H