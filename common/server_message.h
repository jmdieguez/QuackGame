#ifndef COMMON_SERVER_MESSAGE_H
#define COMMON_SERVER_MESSAGE_H

#include <cstdint>

class ServerMessage {
public:
    const uint16_t code; // crear un enum con los diferentes tipos de msj

    ServerMessage(uint16_t &c) : code(c) {}

    ~ServerMessage() {}
};

#endif  // COMMON_CLIENT_COMMAND_H
