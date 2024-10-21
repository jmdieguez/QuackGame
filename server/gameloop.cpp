#include "gameloop.h"

#include <sstream>
#include <string>

#include "../common/defs.h"
#include "../common/client_command.h"

Gameloop::Gameloop(SessionsHandler& h, const std::shared_ptr<Queue<ClientCommand>>& recv_q):
        constant_rate_loop(_keep_running, FRAME_RATE, [this](unsigned int step) { this->step(step); }),
        handler(h),
        recv_queue(recv_q) {}

void Gameloop::run() {
    constant_rate_loop.execute();
}

void Gameloop::step(unsigned int current_step) {
    try {
        std::cout << "current_step: " << current_step << std::endl;
        /* ClientCommand command;
        while (recv_queue->try_pop(command)) {
            // interpretar comando
        } */
        
        // simular juego

        // enviar info a clientes
        GameDTO game_dto = game.get_status();
    } catch (ClosedQueue& e) {}
}
