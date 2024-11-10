#include "server.h"

#include <iostream>
#include <string>
#define QUIT "q"

Server::Server(const char* port):
        open(true),
        acceptor(port) {}

Server::~Server() {}

int Server::run() {
    acceptor.start();

    std::string line;
    while (open && acceptor.is_alive()) {
        std::getline(std::cin, line);
        if (line == QUIT) {
            open = false;
            acceptor.stop();
        }
    }

    acceptor.join();
    return SUCCESS;
}
