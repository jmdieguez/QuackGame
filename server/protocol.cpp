
#include "protocol.h"

#include <arpa/inet.h>


ServerProtocol::ServerProtocol(Socket& socket): skt(socket) {}

void ServerProtocol::read_actions(ActionMessage& action_message, bool& was_closed) {
    uint8_t id = 0;
    skt.recvall(&id, sizeof(id), &was_closed);
    if (was_closed)
    {
        return;
    }
    uint8_t action = 0;
    skt.recvall(&action, sizeof(action), &was_closed);
    if (was_closed)
    {
        return;
    }
    action_message.id = id;
    action_message.action = action;
}

void ServerProtocol::send_snapshot(const Snapshot& snapshot, bool& was_closed) {
    // send amount of duck must read
    uint8_t number_of_ducks = snapshot.ducks.size();
    skt.sendall(&number_of_ducks, sizeof(uint8_t), &was_closed);
    if (was_closed) {
        return;
    }
    for (DuckSnapshot duck: snapshot.ducks) {
        // send duck information
        uint8_t id = htons(duck.id);
        skt.sendall(&id , sizeof(id), &was_closed);
        if (was_closed) {
            break;
        }
        uint8_t action = static_cast<uint8_t>(htons(duck.current_action));
        skt.sendall(&action, sizeof(action), &was_closed);
        if (was_closed) {
            break;
        }
        uint8_t pos_x = static_cast<uint8_t>(htons(duck.position.pos_x));
        skt.sendall(&pos_x, sizeof(pos_x), &was_closed);
        if (was_closed) {
            break;
        }
        uint8_t pos_y = static_cast<uint8_t>(htons(duck.position.pos_y));
        skt.sendall(&pos_y, sizeof(pos_y), &was_closed);
        if (was_closed) {
            break;
        }
    }
}
