#include "receiver.h"
#include "protocol.h"
#include "../../common/liberror.h"

Receiver::Receiver(Socket& skt, Queue<Snapshot>& recv_q) :
        protocol(skt), recv_queue(recv_q), closed(false){}

Receiver::~Receiver() {}

void Receiver::run() {
    try {
        while (!closed && _keep_running) {
            Snapshot snapshot;
            protocol.read_snapshot(snapshot, closed);
            if (!closed) {
                try {
                    recv_queue.push(snapshot);
                } catch (ClosedQueue& e) {
                    return;
                }
            }
        }
    } catch (LibError& e) {}
}
