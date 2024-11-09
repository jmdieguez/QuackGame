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
    bool is_shooting;
    bool is_droping;
    bool is_grabing;
    Queue<ClientActionType> &queue_sender;

public:
    explicit GameContext(Queue<ClientActionType> &queue_sender);
    void set_left_direction_active(bool value);
    bool is_left_direction_pressed();
    void set_right_direction_active(bool value);
    bool is_right_direction_pressed();
    void set_bent_down_active(bool value);
    bool is_bent_down_pressed();
    void set_shooting_active(bool value);
    bool is_shooting_pressed();
    void set_droping_active(bool value);
    bool is_droping_pressed();
    void set_grabing_active(bool value);
    bool is_grabing_pressed();
    void push_message(ClientActionType action);
    ~GameContext();
};

#endif // GAME_CONTEXT_H