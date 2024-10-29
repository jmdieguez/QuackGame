#include "gamecontext.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

GameContext::GameContext(Queue<ClientActionType> &queue_sender) : left_direction(false), right_direction(false),
                                                                  is_bent_down(false),
                                                                  queue_sender(queue_sender)
{
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

void GameContext::push_message(ClientActionType action)
{
    queue_sender.try_push(action);
}

GameContext::~GameContext()
{
}
