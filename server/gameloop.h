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
    ConstantRateLoop constant_rate_loop;
    Queue<ClientCommand> game_queue;
    Game game;
    SessionsHandler handler;
public:
    Gameloop(const uint16_t& id, const uint16_t& creator_id);
    void run() override;
    void step(unsigned int current_step);
    Queue<ClientCommand>* add_new_player(const uint16_t&, Queue<Snapshot>&);
    void start_game(const uint16_t&);
    const std::string& get_name();
    void game_state(std::atomic<bool>&);
};

#endif // GAMELOOP_H
