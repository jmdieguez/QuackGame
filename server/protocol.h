#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include "../common/snapshots.h"
#include "../common/client_actions.h"
#include "../common/lobby_messages.h"
#include "../common/socket.h"
#include <vector>

class ServerProtocol {
private:
    Socket& skt;
    void send_data(const uint16_t& data);
    void send_duck_status(const DuckStatus& status);
    void send_duck(const DuckSnapshot& duck);
    void send_position(const PositionSnapshot& pos);
    void send_name(const std::vector<unsigned char>&);
public:
    explicit ServerProtocol(Socket&);
    ActionMessage read_action();
    ActionLobby read_lobby();
    void send_snapshot(const Snapshot& snapshot);
    void send_lobby_info(const LobbyMessage&);
};

#endif  // SERVER_PROTOCOL_H
