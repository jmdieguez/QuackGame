#include "gamecontext.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

GameContext::GameContext(Queue<ClientActionType> &queue_sender) : queue_sender(queue_sender), looking_up(false), left_direction(false), right_direction(false),
                                                                  is_bent_down(false), is_shooting(false), is_droping(false), is_grabing(false),
                                                                  is_jumping(false)

{
}

void GameContext::push_message(ClientActionType action)
{
    queue_sender.try_push(action);
}

GameContext::~GameContext()
{
}
