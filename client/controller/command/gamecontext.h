#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include "../common/queue.h"
#include "../common/client_actions.h"

class GameContext
{
private:
    Queue<ClientActionType> &queue_sender;

public:
    bool looking_up;
    bool left_direction;
    bool right_direction;
    bool is_bent_down;
    bool is_shooting;
    bool is_droping;
    bool is_grabing;
    bool is_jumping;

    explicit GameContext(Queue<ClientActionType> &queue_sender);
    void push_message(ClientActionType action);
    ~GameContext();
};

#endif // GAME_CONTEXT_H