#include "gameloop.h"

#include <sstream>
#include <string>

#include "defs.h"

Gameloop::Gameloop(SessionsHandler& h, const std::shared_ptr<Queue<ClientCommand>>& recv_q):
        handler(h), recv_queue(recv_q) {}

void Gameloop::run() {
    try {
        while (_keep_running) {
            ClientCommand command;
            while (recv_queue->try_pop(command)) {
                run_command(command);
            }
            int n_respawned_boxes = game.step();

            for (int i = 0; i < n_respawned_boxes; ++i) {
                std::cout << NEW_BOX_MSG;
                ServerMessage message;  // Respawn message
                handler.broadcast(message);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    } catch (ClosedQueue& e) {}
}

void Gameloop::run_command(const ClientCommand& command) {
    if (command.code == MSG_CODE) {
        Reward reward = game.pickup(command.box_id);
        if (reward.id != RewardID::Undefined) {
            std::ostringstream oss;
            oss << command.name << PICKUP_MSG << reward.name << std::endl;
            std::cout << oss.str();
            ServerMessage message(command.name, command.name_len, reward.id);
            handler.broadcast(message);
        }
    }
}
