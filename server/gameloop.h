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
#include "game/color/colorstorage.h"

class Gameloop : public Thread
{
private:
    uint16_t game_id;
    uint16_t creator_id;
    ColorStorage color_storage;
    std::string name;
    bool started;
    bool finished = false;
    ConstantRateLoop constant_rate_loop;
    std::shared_ptr<Queue<ClientCommand>> recv_queue;
    Game game;
    SessionsHandler handler;
    uint16_t number_of_players;

public:
    Gameloop(const uint16_t &id, const std::string &name, const uint16_t &creator_id);
    ~Gameloop() {}
    void run() override;
    void stop() override;
    void step(unsigned int current_step);
    std::vector<Color> add_new_player(std::vector<uint16_t> &ids);
    void set_session(Socket &skt, std::vector<uint16_t> &ids);
    void start_game(const uint16_t &game_id);
    const std::string &get_name();
    void game_state(std::atomic<bool> &);
    bool has_finished() const { return finished; }
    void get_number_of_players(uint16_t &);
};

#endif // GAMELOOP_H
