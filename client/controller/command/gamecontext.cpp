#include "gamecontext.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

GameContext::GameContext(Queue<ClientActionType> &queue_sender) : is_right_direction(true),
                                                                  is_running(false),
                                                                  is_bent_down(false),
                                                                  queue_sender(queue_sender)
{
}

void GameContext::push_message(ClientActionType action)
{
    queue_sender.try_push(action);
}

GameContext::~GameContext()
{
}
