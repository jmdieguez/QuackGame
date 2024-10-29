#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include "../common/queue.h"
#include "../common/client_actions.h"

class GameContext
{
private:
    bool left_direction;
    bool right_direction;
    bool is_bent_down;
    Queue<ClientActionType> &queue_sender;

public:
    explicit GameContext(Queue<ClientActionType> &queue_sender);
    void set_left_direction_active(bool value);
    bool is_left_direction_pressed();
    void set_right_direction_active(bool value);
    bool is_right_direction_pressed();
    void push_message(ClientActionType action);
    ~GameContext();
};

#endif // GAME_CONTEXT_H