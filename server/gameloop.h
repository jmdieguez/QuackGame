#ifndef SERVER_GAMELOOP_H
#define SERVER_GAMELOOP_H

#include <memory>

#include "queue.h"
#include "thread.h"
#include "sessions_handler.h"

class ClientCommand;

class Gameloop: public Thread {
private:
    // Game game;
    SessionsHandler& handler;
    std::shared_ptr<Queue<ClientCommand>> recv_queue;

public:
    Gameloop(SessionsHandler& h, const std::shared_ptr<Queue<ClientCommand>>& recv_q);
    void run() override;
    void run_command(const ClientCommand& command);
};

#endif  // SERVER_GAMELOOP_H
