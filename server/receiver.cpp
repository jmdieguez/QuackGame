#include "receiver.h"

#include "../common/liberror.h"
#include "protocol.h"

Receiver::Receiver(Socket& skt, const std::shared_ptr<Queue<ClientCommand>>& recv_q):
        client(skt), recv_queue(recv_q), closed(false) {}

Receiver::~Receiver() {}

void Receiver::run() {
    try {
        while (!closed && _keep_running) {
            ClientCommand command = protocol.receive_message(client, &closed);
            if (!closed) {
                try {
                    recv_queue->push(command);
                } catch (ClosedQueue& e) {
                    return;
                }
            }
        }
    } catch (LibError& e) {}
}
