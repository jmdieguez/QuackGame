#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include "../common/queue.h"
#include "../common/client_actions.h"

class GameContext
{
private:
    bool other_direction;
    bool is_bent_down;
    Queue<ClientActionType> &queue_sender;

public:
    explicit GameContext(Queue<ClientActionType> &queue_sender);
    void set_opposite_direction_active(bool value);
    bool is_opposite_direction_pressed();
    void push_message(ClientActionType action);
    ~GameContext();
};

#endif // GAME_CONTEXT_H