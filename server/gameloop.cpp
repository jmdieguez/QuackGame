#include "gameloop.h"
#include "../common/defs.h"
#include "client_command.h"

Gameloop::Gameloop(const uint16_t& id, const uint16_t& creator_id):
        game_id(id), creator_id(creator_id), started(false),
        constant_rate_loop(_keep_running, [this](unsigned int step) { this->step(step); }),
        game_queue(std::make_shared<Queue<ClientCommand>>(100)), game("map.yaml") {}

void Gameloop::run() {
    started = true;
    constant_rate_loop.execute();
}

void Gameloop::step([[maybe_unused]] unsigned int current_step) {
    try {
        ClientCommand command;
        while (game_queue->try_pop(command)) {
            game.process(command);
        }
        game.step();
        Snapshot snapshot = game.get_status();
        handler.broadcast(snapshot);
    } catch (ClosedQueue& e) {} 
}

void Gameloop::start_game(const uint16_t& id) {
    if (id == creator_id) {
        this->start();
    }
}

void Gameloop::add_new_player(const uint16_t& id, Queue<Snapshot>& sender_queue) {
    handler.add(sender_queue, id);
}

const std::string& Gameloop::get_name() {
    return name;
}

void Gameloop::game_state(std::atomic<bool>& state) {
    state = started;
}