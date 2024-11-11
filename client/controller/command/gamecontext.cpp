#include "gamecontext.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

GameContext::GameContext(Queue<ClientActionType> &queue_sender) : looking_up(false), left_direction(false), right_direction(false),
                                                                  is_bent_down(false), is_shooting(false), is_droping(false), is_grabing(false),
                                                                  is_jumping(false),
                                                                  queue_sender(queue_sender)
{
}

void GameContext::set_looking_up_active(bool value)
{
    looking_up = value;
}

bool GameContext::is_looking_up_pressed()
{
    return looking_up;
}

void GameContext::set_left_direction_active(bool value)
{
    left_direction = value;
}

bool GameContext::is_left_direction_pressed()
{
    return left_direction;
}

void GameContext::set_right_direction_active(bool value)
{
    right_direction = value;
}

bool GameContext::is_right_direction_pressed()
{
    return right_direction;
}

void GameContext::set_bent_down_active(bool value)
{
    is_bent_down = value;
}

bool GameContext::is_bent_down_pressed()
{
    return is_bent_down;
}

void GameContext::set_shooting_active(bool value)
{
    is_shooting = value;
}

bool GameContext::is_shooting_pressed()
{
    return is_shooting;
}

void GameContext::set_droping_active(bool value)
{
    is_droping = value;
}

bool GameContext::is_droping_pressed()
{
    return is_droping;
}

void GameContext::set_grabing_active(bool value)
{
    is_grabing = value;
}

bool GameContext::is_grabing_pressed()
{
    return is_grabing;
}

void GameContext::set_jumping_active(bool value)
{
    is_jumping = value;
}

bool GameContext::is_jumping_pressed()
{
    return is_jumping;
}

void GameContext::push_message(ClientActionType action)
{
    queue_sender.try_push(action);
}

GameContext::~GameContext()
{
}
