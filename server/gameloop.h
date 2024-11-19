#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <memory>
#include <iostream>
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
    bool finished = false;
    ConstantRateLoop constant_rate_loop;
    std::shared_ptr<Queue<ClientCommand>> recv_queue;
    Game game;
    SessionsHandler handler;
public:
    Gameloop(const uint16_t& id, const std::string&, const uint16_t& creator_id);
    ~Gameloop() {}
    void run() override;
    void stop() override;
    void step(unsigned int current_step);
    void add_new_player(Socket &skt, const uint16_t& id);
    void start_game(const uint16_t& game_id);
    const std::string& get_name();
    void game_state(std::atomic<bool>&);
    bool has_finished() const { return finished; }
};

#endif // GAMELOOP_H
