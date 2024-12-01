#include "sessioncontroller.h"

#define MAX_MESSAGES_QUEUE_RECEIVER 100000
#define MAX_MESSAGES_QUEUE_SENDER 100000

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

SessionController::SessionController(std::vector<UserLobbyInfo> &users) : queue_receiver(MAX_MESSAGES_QUEUE_RECEIVER),
                                                                          queue_sender(MAX_MESSAGES_QUEUE_SENDER),
                                                                          player_one_input(queue_sender, config_manager.get_player_config(0)),
                                                                          player_two_input(queue_sender, config_manager.get_player_config(1)),
                                                                          num_players(users.size())
{
    player_one_input.set_id(users[0].get_id());
    if (users.size() == 1)
        return;
    player_two_input.set_id(users[1].get_id());
}

Queue<Snapshot> &SessionController::get_queue_receiver()
{
    return queue_receiver;
}

void SessionController::process_input(SDL_Event &event)
{
    player_one_input.execute_command(event, cheat_storage);
    if (num_players == 1)
        return;
    player_two_input.execute_command(event, cheat_storage);
}

void SessionController::revert_command(SDL_Event &event)
{
    player_one_input.undo_command(event);
    if (num_players == 1)
        return;
    player_two_input.undo_command(event);
}

Queue<ClientIdAction> &SessionController::get_queue_sender()
{
    return queue_sender;
}

SessionController::~SessionController()
{
}
