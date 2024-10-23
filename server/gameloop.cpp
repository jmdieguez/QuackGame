#include "gameloop.h"
#include "../common/defs.h"
#include "client_command.h"

Gameloop::Gameloop(SessionsHandler& h, const std::shared_ptr<Queue<ClientCommand>>& recv_q):
        constant_rate_loop(_keep_running, FRAME_RATE, [this](unsigned int step) { this->step(step); }),
        handler(h),
        recv_queue(recv_q) {}

void Gameloop::run() {
    constant_rate_loop.execute();
}

void Gameloop::step([[maybe_unused]] unsigned int current_step) {
    try {
        ClientCommand command;
        while (recv_queue->try_pop(command)) {
            game.process(command);
        }
        
        // simular juego
        game.step();
        // enviar info a clientes
        Snapshot snapshot = game.get_status();
    } catch (ClosedQueue& e) {}
}
