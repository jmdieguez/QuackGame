#ifndef SERVER_GAMELOOP_H
#define SERVER_GAMELOOP_H

#include <memory>

#include "client_command.h"
#include "../common/constant_rate_loop.h"
#include "../common/queue.h"
#include "../common/thread.h"
#include "sessions_handler.h"
#include "./game/game.h"

class Gameloop: public Thread {
private:
    ConstantRateLoop constant_rate_loop;
    SessionsHandler& handler;
    std::shared_ptr<Queue<ClientCommand>> recv_queue;
    Game game;
public:
    Gameloop(SessionsHandler& h, const std::shared_ptr<Queue<ClientCommand>>& recv_q);
    void run() override;
    void step(unsigned int current_step);
};

#endif  // SERVER_GAMELOOP_H
