#include "protocol.h"

#include <string>

#include <arpa/inet.h>

#include "../common/liberror.h"

ServerProtocol::ServerProtocol() {}

ServerProtocol::~ServerProtocol() {}

/*

ClientCommand ServerProtocol::receive_message(Socket& skt, bool* closed) {
    uint8_t code, box_id;
    uint16_t name_length, name_length_host;

    if (skt.recvall(&code, sizeof(uint8_t), closed) != sizeof(uint8_t) || *closed)
        throw LibError(errno, "error while receiving code");
    if (skt.recvall(&name_length, sizeof(uint16_t), closed) != sizeof(uint16_t) || *closed)
        throw LibError(errno, "error while receiving client's name length");

    name_length_host = ntohs(name_length);
    std::string name(name_length_host, ' ');

    if (skt.recvall(name.data(), name_length_host, closed) != name_length_host || *closed)
        throw LibError(errno, "error while receiving client's name");
    if (skt.recvall(&box_id, sizeof(uint8_t), closed) != sizeof(uint8_t) || *closed)
        throw LibError(errno, "error while receiving box id");

    return ClientCommand(name, name_length_host, static_cast<BoxID>(box_id));
}

void ServerProtocol::send_message(Socket& skt, ServerMessage& message, bool* closed) {
    if (skt.sendall(&message.code, sizeof(uint8_t), closed) != sizeof(uint8_t) || *closed)
        throw LibError(errno, "error while sending code");
    if (skt.sendall(&message.action, sizeof(uint8_t), closed) != sizeof(uint8_t) || *closed)
        throw LibError(errno, "error while sending action");
    if (message.action == BOX_TAKEN) {

        uint16_t name_len_network = htons(message.name_len);
        if (skt.sendall(&name_len_network, sizeof(uint16_t), closed) != sizeof(uint16_t) || *closed)
            throw LibError(errno, "error while sending the client's name length");
        if (skt.sendall(message.name.data(), message.name_len, closed) != message.name_len ||
            *closed)
            throw LibError(errno, "error while sending the client's name");
        if (skt.sendall(&message.reward_id, sizeof(uint8_t), closed) != sizeof(uint8_t) || *closed)
            throw LibError(errno, "error while sending the reward id");
    }
}

*/