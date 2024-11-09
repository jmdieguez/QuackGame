#include "gameloop.h"
#include "../common/defs.h"
#include "client_command.h"

Gameloop::Gameloop(SessionsHandler &h, const std::shared_ptr<Queue<ClientCommand>> &recv_q) : constant_rate_loop(_keep_running, [this](unsigned int step)
                                                                                                                 { this->step(step); }),
                                                                                              handler(h), recv_queue(recv_q), game("server/game/maps/map_00.yaml") {}

void Gameloop::run()
{

    constant_rate_loop.execute();
}

void Gameloop::step([[maybe_unused]] unsigned int current_step)
{
    try
    {
        ClientCommand command;
        while (recv_queue->try_pop(command))
            game.process(command);
        game.step();
        Snapshot snapshot = game.get_status();
        handler.broadcast(snapshot);
    }
    catch (ClosedQueue &e)
    {
    }
}
