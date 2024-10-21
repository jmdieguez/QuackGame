#include "sender.h"

#include "../common/liberror.h"
#include "protocol.h"

Sender::Sender(Socket& skt): client(skt) {}

Sender::~Sender() {}

void Sender::run() {
    try {
        ServerProtocol protocol;
        while (!closed && _keep_running) {
            try {
                ServerMessage message = out_queue.pop();
                protocol.send_message(client, message, &closed);
            } catch (ClosedQueue& e) {
                return;
            }
        }
    } catch (LibError& e) {}
}

void Sender::stop() { out_queue.close(); }

void Sender::send(const ServerMessage& msg) { out_queue.push(msg); }
