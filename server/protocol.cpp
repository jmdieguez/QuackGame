
#include "protocol.h"
#include "../common/liberror.h"
#include <arpa/inet.h>

ServerProtocol::ServerProtocol(Socket &socket) : skt(socket) {}

ActionMessage ServerProtocol::read_action()
{
    ClientActionType action;
    bool was_closed = false;

    uint16_t info;
    skt.recvall(&info, sizeof(info), &was_closed);
    if (was_closed)
    {
        throw LibError(errno, "Error al intentar enviar datos a cliente");
    }
    action = static_cast<ClientActionType>(ntohs(info));
    return ActionMessage(action, "");
}

ActionLobby ServerProtocol::read_lobby()
{
    ClientActionType action;
    bool was_closed = false;

    uint16_t info;
    skt.recvall(&info, sizeof(info), &was_closed);
    if (was_closed)
    {
        throw LibError(errno, "Error al intentar enviar datos a cliente");
    }
    action = static_cast<ClientActionType>(ntohs(info));
    uint16_t game_id = 0;
    if (action == ClientActionType::START_GAME || action == ClientActionType::JOIN_GAME) {
        skt.recvall(&game_id, sizeof(game_id), &was_closed);
        if (was_closed)
        {
            throw LibError(errno, "Error al intentar enviar datos a cliente");
        }
        game_id = ntohs(game_id);
    }
    return ActionLobby(action, game_id);
}

void ServerProtocol::send_data(const uint16_t &data)
{
    bool was_closed = false;
    uint16_t info = htons(data);
    skt.sendall(&info, sizeof(uint16_t), &was_closed);
    if (was_closed)
    {
        throw LibError(errno, "Error al intentar enviar datos a cliente");
    }
}

void ServerProtocol::send_duck(const DuckSnapshot &duck)
{
    send_data(duck.id);
    send_data(duck.position.pos_x);
    send_data(duck.position.pos_y);
    send_data(static_cast<uint16_t>(duck.current_action));
    send_data(duck.right_direction ? 1 : 0);

    //    send_duck_status(duck.status);
    //   send_data(static_cast<uint16_t>(duck.gun));
}

void ServerProtocol::send_duck_status(const DuckStatus &status)
{
    send_data(static_cast<uint16_t>(status.has_chestplate));
    send_data(static_cast<uint16_t>(status.shooting));
    send_data(static_cast<uint16_t>(status.looking_right));
    send_data(static_cast<uint16_t>(status.looking_up));
    send_data(static_cast<uint16_t>(status.has_helmet));
    send_data(static_cast<uint16_t>(status.is_alive));
}

void ServerProtocol::send_snapshot(const Snapshot &snapshot)
{
    const uint16_t cant_ducks = static_cast<uint16_t>(snapshot.ducks.size());
    send_data(cant_ducks);
    for (const DuckSnapshot &duck : snapshot.ducks)
    {
        send_duck(duck);
    }
}

void ServerProtocol::send_lobby_info(const LobbyMessage& lobby) {
    send_data(lobby.game_id);

    uint16_t nameLength = static_cast<uint16_t>(lobby.name.length());
    send_data(nameLength);

    std::vector<unsigned char> nameBytes(lobby.name.begin(), lobby.name.end());
    send_name(nameBytes);
}

void ServerProtocol::send_name(const std::vector<unsigned char>& data) {
    bool was_closed = false;
    skt.sendall(data.data(), data.size(), &was_closed);
    if (was_closed) {
        throw LibError(errno, "Error al intentar enviar datos a cliente");
    }
}