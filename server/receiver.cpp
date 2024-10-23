#include "receiver.h"
#include "protocol.h"
#include "../common/liberror.h"
#include "../common/client_command.h"

Receiver::Receiver(Socket& skt, const std::shared_ptr<Queue<ActionMessage>>& recv_q):
        client(skt), recv_queue(recv_q), protocol(skt), closed(false){}

Receiver::~Receiver() {}

void Receiver::run() {
    try {
        while (!closed && _keep_running) {
            protocol.read_actions(client, &closed);
            if (!closed) {
                try {
                    // recv_queue->push(command);
                } catch (ClosedQueue& e) {
                    return;
                }
            }
        }
    } catch (LibError& e) {}
}
