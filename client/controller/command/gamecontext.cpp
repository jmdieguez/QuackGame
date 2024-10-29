#include "gamecontext.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

GameContext::GameContext(Queue<ClientActionType> &queue_sender) : other_direction(false),
                                                                  is_bent_down(false),
                                                                  queue_sender(queue_sender)
{
}

void GameContext::set_opposite_direction_active(bool value)
{
    other_direction = value;
}

bool GameContext::is_opposite_direction_pressed()
{
    return other_direction;
}

void GameContext::push_message(ClientActionType action)
{
    queue_sender.try_push(action);
}

GameContext::~GameContext()
{
}
