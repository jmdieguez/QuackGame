
#include "protocol.h"
#include "../common/liberror.h"
#include <arpa/inet.h>


ServerProtocol::ServerProtocol(Socket& socket): skt(socket) {}

ActionMessage ServerProtocol::read_action() {
    ClientActionType action;
    bool was_closed = false;
    skt.recvall(&action, sizeof(action), &was_closed);
    if (was_closed) {
        throw LibError(errno, "Error al intentar enviar datos a cliente");
    }
    return ActionMessage(action, "");
}

void ServerProtocol::send_data(const void* data) {
    bool was_closed = false;
    skt.sendall(data, sizeof(uint8_t), &was_closed);
    if (was_closed) {
        throw LibError(errno, "Error al intentar enviar datos a cliente");
    }
}

void ServerProtocol::send_duck(const DuckSnapshot& duck) {
    send_data(&(duck.id));
    send_position(duck.position);
    send_data(&duck.current_action);
    send_duck_status(duck.status);
    send_data(&(duck.gun));
}

void ServerProtocol::send_duck_status(const DuckStatus& status) {
    send_data(&status.has_chestplate);
    send_data(& status.shooting);
    send_data(&status.looking_right);
    send_data(&status.looking_up);
    send_data(&status.has_helmet);
    send_data(&status.is_alive);
}

void ServerProtocol::send_position(const PositionSnapshot& pos) {
    send_data(&pos.pos_x);
    send_data(&pos.pos_y);
}

void ServerProtocol::send_snapshot(const Snapshot& snapshot)
{
    const auto cant_ducks = static_cast<uint8_t>(snapshot.ducks.size());
    send_data(&cant_ducks);
    for (const DuckSnapshot& duck : snapshot.ducks) {
        send_duck(duck);
    }
}

