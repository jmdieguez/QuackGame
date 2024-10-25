#include "protocol.h"
#include <arpa/inet.h>

ClientProtocol::ClientProtocol(Socket& skt) : skt(skt) {}

void ClientProtocol::read_snapshot(Snapshot& snapshot, bool& was_closed) {
    skt.recvall(&snapshot, sizeof(snapshot), &was_closed);
}

void ClientProtocol::send_action(const ClientActionType& action, bool& was_closed) {
    skt.sendall(&action, sizeof(action), &was_closed);
}


