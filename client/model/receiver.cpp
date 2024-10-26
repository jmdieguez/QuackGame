#include "receiver.h"
#include "protocol.h"
#include "../../common/liberror.h"

Receiver::Receiver(Socket& skt, Queue<Snapshot>& recv_q) :
        protocol(skt), recv_queue(recv_q) {}

Receiver::~Receiver() {}

void Receiver::run() {
    try {
        while (_keep_running) {
            Snapshot snapshot;
            protocol.read_snapshot(snapshot);
            recv_queue.push(snapshot);
        }
    } catch (ClosedQueue& e) {} catch (LibError& e) {}
}

void Receiver::stop() {
    _keep_running = false;
    recv_queue.close();
}