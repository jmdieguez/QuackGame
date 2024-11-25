#include "gameloop.h"
#include "../common/defs.h"
#include "client_command.h"

Gameloop::Gameloop(const uint16_t &id, const std::string &name, const uint16_t &creator_id) : game_id(id), creator_id(creator_id), name(name), started(false),
                                                                                              constant_rate_loop(_keep_running, [this](unsigned int step)
                                                                                                                 { this->step(step); }),
                                                                                              recv_queue(std::make_shared<Queue<ClientCommand>>(10000)),
                                                                                              handler(recv_queue),
                                                                                              number_of_players(1)
{
}

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
    if (game.ended || !handler.has_clients())
    {
        _keep_running = false;
        finished = true;
        return;
    }

    try
    {
        ClientCommand command;
        while (recv_queue->try_pop(command))
        {
            game.process(command);
        }
        game.step();
        Snapshot snapshot = game.get_status();
        handler.remove_closed_sessions();
        handler.broadcast(snapshot);
    }
    catch (ClosedQueue &e)
    {
    }
}

void Gameloop::start_game(const uint16_t &id)
{
    if (id == creator_id && number_of_players > 1)
    {
        this->start();
    }
}

void Gameloop::add_new_player(Socket &skt, const uint16_t &id)
{
    Color color = color_storage.get_color();
    handler.add(skt, id);
    game.add_player(id, color);
    number_of_players++;
}

const std::string &Gameloop::get_name()
{
    return name;
}

void Gameloop::game_state(std::atomic<bool> &state)
{
    state = started;
}

void Gameloop::get_number_of_players(uint16_t &amount)
{
    amount = number_of_players;
}