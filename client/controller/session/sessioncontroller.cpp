#include "sessioncontroller.h"

#define MAX_MESSAGES_QUEUE_RECEIVER 100000
#define MAX_MESSAGES_QUEUE_SENDER 100000

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

SessionController::SessionController() : queue_receiver(MAX_MESSAGES_QUEUE_RECEIVER),
                                         queue_sender(MAX_MESSAGES_QUEUE_SENDER), input(queue_sender),
                                         game_context(queue_sender)
{
}

Queue<Snapshot> &SessionController::get_queue_receiver()
{
    return queue_receiver;
}

void SessionController::process_input(SDL_Event &event)
{
    input.execute_command(event, game_context, cheat_storage);
}

void SessionController::revert_command(SDL_Event &event)
{
    input.undo_command(event, game_context);
}

Queue<ClientActionType> &SessionController::get_queue_sender()
{
    return queue_sender;
}

SessionController::~SessionController()
{
}
