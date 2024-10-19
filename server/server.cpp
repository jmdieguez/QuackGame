#include "server_server.h"

#include <iostream>
#include <string>
#define QUIT "q"

Server::Server(const char* port):
        open(true),
        recv_queue(std::make_shared<Queue<ClientCommand>>()),
        handler(recv_queue),
        gameloop(handler, recv_queue),
        acceptor(port, handler) {}

Server::~Server() {}

int Server::run() {
    gameloop.start();
    acceptor.start();

    std::string line;
    while (open && acceptor.is_alive()) {
        std::getline(std::cin, line);
        if (line == QUIT) {
            open = false;
            acceptor.stop();
            gameloop.stop();
        }
    }

    acceptor.join();
    gameloop.join();
    return SUCCESS;
}
