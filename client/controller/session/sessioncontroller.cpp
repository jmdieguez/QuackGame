#include "sessioncontroller.h"

#define MAX_MESSAGES_QUEUE_RECEIVER 100000
#define MAX_MESSAGES_QUEUE_SENDER 100000

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

bool SessionController::is_player1_input(const SDL_Keycode &key, const PlayerKeyConfigManager &config_manager)
{
    const auto &player1_keys = config_manager.get_player_config(0).get_key_command_map();
    return player1_keys.find(key) != player1_keys.end();
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

SessionController::SessionController() : queue_receiver(MAX_MESSAGES_QUEUE_RECEIVER),
                                         queue_sender(MAX_MESSAGES_QUEUE_SENDER),
                                         player_one_input(queue_sender, config_manager.get_player_config(0)),
                                         player_two_input(queue_sender, config_manager.get_player_config(1)),
                                         game_context(queue_sender)
{
}

Queue<Snapshot> &SessionController::get_queue_receiver()
{
    return queue_receiver;
}

void SessionController::process_input(SDL_Event &event)
{
    is_player1_input(event.key.keysym.sym, config_manager) ? player_one_input.execute_command(event, game_context, cheat_storage) : player_two_input.execute_command(event, game_context, cheat_storage);
}

void SessionController::revert_command(SDL_Event &event)
{
    is_player1_input(event.key.keysym.sym, config_manager) ? player_one_input.undo_command(event, game_context) : player_two_input.undo_command(event, game_context);
}

Queue<ClientActionType> &SessionController::get_queue_sender()
{
    return queue_sender;
}

SessionController::~SessionController()
{
}
