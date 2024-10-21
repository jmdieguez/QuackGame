#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <memory>

#include "../common/client_command.h"
#include "../common/socket.h"

class ServerMessage;

class ServerProtocol {
public:
    ServerProtocol();
    ~ServerProtocol();

    ClientCommand receive_message(Socket& skt, bool* closed);
    void send_message(Socket& skt, ServerMessage& message, bool* closed);
};

#endif  // SERVER_PROTOCOL_H
