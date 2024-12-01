#ifndef SESSION_CONTROLLER_H
#define SESSION_CONTROLLER_H

#include "cheat/cheatstorage.h"
#include "command/inputhandler.h"
#include "command/gamecontext.h"
#include "command/playerkeyconfigmanager.h"
#include "../../../common/userlobbyinfo.h"
#include "../../../common/queue.h"
#include "../../../common/snapshots.h"

class SessionController
{
private:
    CheatStorage cheat_storage;
    Queue<Snapshot> queue_receiver;
    Queue<ClientIdAction> queue_sender;
    PlayerKeyConfigManager config_manager;
    InputHandler player_one_input;
    InputHandler player_two_input;
    uint16_t num_players;

    bool is_player1_input(const SDL_Keycode &key, const PlayerKeyConfigManager &config_manager);

public:
    explicit SessionController(std::vector<UserLobbyInfo> &users);
    Queue<Snapshot> &get_queue_receiver();
    void process_input(SDL_Event &event);
    void revert_command(SDL_Event &event);
    Queue<ClientIdAction> &get_queue_sender();
    ~SessionController();
};

#endif // SESSION_CONTROLLER_H