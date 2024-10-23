
#include "protocol.h"
#include "../common/liberror.h"
#include <arpa/inet.h>


ServerProtocol::ServerProtocol(Socket& socket): skt(socket) {}

ActionMessage ServerProtocol::read_actions(bool& was_closed) {
    /* uint8_t id = 0; Esto se debería guardar en el servidor, sino un cliente puede hacerse pasar por otro
    skt.recvall(&id, sizeof(id), &was_closed);
    if (was_closed)
    {
        return;
    } */
    ClientActionType action;
    skt.recvall(&action, sizeof(action), &was_closed);
    if (was_closed) {
        throw LibError(errno, "Error al recibir una acción del usuario");
    }
    
    return ActionMessage(action, "");
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
        uint8_t id = duck.id;
        skt.sendall(&id , sizeof(id), &was_closed);
        if (was_closed) {
            break;
        }
        uint8_t action = static_cast<uint8_t>(duck.current_action);
        skt.sendall(&action, sizeof(action), &was_closed);
        if (was_closed) {
            break;
        }
        uint16_t pos_x = htons(duck.position.pos_x);
        skt.sendall(&pos_x, sizeof(pos_x), &was_closed);
        if (was_closed) {
            break;
        }
        uint16_t pos_y = htons(duck.position.pos_y);
        skt.sendall(&pos_y, sizeof(pos_y), &was_closed);
        if (was_closed) {
            break;
        }
    }
}
