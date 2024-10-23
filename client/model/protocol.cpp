#include "protocol.h"
#include <arpa/inet.h>

// ClientProtocol::ClientProtocol(Socket &socket) : skt(socket) {}

ClientProtocol::ClientProtocol()
{
}

bool ClientProtocol::read(uint8_t &info)
{
    (void)info;
    bool was_closed = false;
    // skt.recvall(&info, sizeof(info), &was_closed);
    return was_closed;
}

// bool ClientProtocol::readDuck(Duck &newDuck) {
//     uint8_t id = 0;
//     bool was_closed = false;
//     skt.recvall(&id, sizeof(id), &was_closed);
//     if (was_closed) {
//         return was_closed;
//     }

//     uint8_t action = 0;
//     skt.recvall(&action, sizeof(action), &was_closed);
//     if (was_closed) {
//         return was_closed;
//     }

//     uint8_t pos_x = 0;
//     skt.recvall(&pos_x, sizeof(pos_x ), &was_closed);
//     if (was_closed) {
//         return was_closed;
//     }

//     uint8_t pos_y = 0;
//     skt.recvall(&pos_y, sizeof(pos_y), &was_closed);
//     if (was_closed) {
//         return was_closed;
//     }

//     newDuck.id = ntohs(id);
//     newDuck.action = ntohs(action);
//     newDuck.pos_x = ntohs(pos_x);
//     newDuck.pos_y = ntohs(pos_y);
//     return was_closed;
// }

// void ClientProtocol::send(const ActionMessage &actionMessage, bool &was_closed)
// {
//     uint8_t id = actionMessage.id;
//     uint8_t action = actionMessage.action;
//     skt.sendall(&id, sizeof(id), &was_closed);
//     if (was_closed)
//     {
//         return;
//     }
//     skt.sendall(&action, sizeof(action), &was_closed);
//     if (was_closed)
//     {
//         return;
//     }
// }
