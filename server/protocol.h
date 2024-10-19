#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <memory>

#include "common_client_command.h"
#include "common_server_message.h"
#include "common_socket.h"

class ServerProtocol {
public:
    ServerProtocol();
    ~ServerProtocol();

    ClientCommand receive_message(Socket& skt, bool* closed);
    void send_message(Socket& skt, ServerMessage& message, bool* closed);
};

#endif  // SERVER_PROTOCOL_H
