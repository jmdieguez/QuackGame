#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <memory>
#include "client_command.h"
#include "../common/constant_rate_loop.h"
#include "../common/queue.h"
#include "../common/thread.h"
#include "sessions_handler.h"
#include "./game/game.h"

class Gameloop : public Thread {
private:
    uint16_t game_id;
    uint16_t creator_id;
    std::string name;
    bool started;
    ConstantRateLoop constant_rate_loop;
    std::shared_ptr<Queue<ClientCommand>> game_queue;
    Game game;
    SessionsHandler handler;
    uint16_t max_player_quantity = 0;
public:
    Gameloop(const uint16_t& id, const uint16_t& creator_id);
    void run() override;
    void step(unsigned int current_step);
    void add_new_player(const uint16_t&, Queue<Snapshot>&);
    void start_game(const uint16_t&);
    const std::string& get_name();
    void game_state(std::atomic<bool>&);
};

#endif // GAMELOOP_H
