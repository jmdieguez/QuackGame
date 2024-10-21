#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <memory>

#include "../common/defs.h"
#include "acceptor.h"
#include "gameloop.h"
#include "sessions_handler.h"

class Server {
private:
    bool open;
    std::shared_ptr<Queue<ClientCommand>> recv_queue;
    SessionsHandler handler;
    Gameloop gameloop;
    Acceptor acceptor;

public:
    explicit Server(const char* port);
    ~Server();
    int run();
};

#endif  // SERVER_SERVER_H
