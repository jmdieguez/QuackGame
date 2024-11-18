#include "gameloop.h"
#include "../common/defs.h"
#include "client_command.h"

Gameloop::Gameloop(const uint16_t& id, const std::string& name, const uint16_t& creator_id):
        game_id(id), creator_id(creator_id), name(name), started(false),
        constant_rate_loop(_keep_running, [this](unsigned int step) { this->step(step); }),
        recv_queue(std::make_shared<Queue<ClientCommand>>(10000)),
        handler(recv_queue) {}


void Gameloop::stop()
{   
    _keep_running = false;
    handler.remove_all_sessions();
}

void Gameloop::run()
{   
    constant_rate_loop.execute();
}

void Gameloop::step([[maybe_unused]] unsigned int current_step)
{
    if (game.started) {
        if (game.ended || !handler.has_clients())
            _keep_running = false;
        try
        {   
            ClientCommand command;
            while (recv_queue->try_pop(command)) {
                game.process(command);
            }
            game.step();
            Snapshot snapshot = game.get_status();
            handler.broadcast(snapshot);
        } catch (ClosedQueue &e)
        {}
    }
}

void Gameloop::start_game(const uint16_t& id) {
    if (id == creator_id) {
        this->start();
    }
}

void Gameloop::add_new_player(Socket &skt, const uint16_t& id) {
    handler.add(skt, id);
    game.add_player(id);
}

const std::string& Gameloop::get_name() {
    return name;
}

void Gameloop::game_state(std::atomic<bool>& state) {
    state = started;
}
