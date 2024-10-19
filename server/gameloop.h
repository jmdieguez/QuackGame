#ifndef SERVER_GAMELOOP_H
#define SERVER_GAMELOOP_H

#include <memory>

#include "common_thread.h"
#include "server_game.h"
#include "server_sessions_handler.h"

class Gameloop: public Thread {
private:
    Game game;
    SessionsHandler& handler;
    std::shared_ptr<Queue<ClientCommand>> recv_queue;

public:
    Gameloop(SessionsHandler& h, const std::shared_ptr<Queue<ClientCommand>>& recv_q);
    void run() override;
    void run_command(const ClientCommand& command);
};

#endif  // SERVER_GAMELOOP_H
