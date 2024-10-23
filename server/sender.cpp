#include "sender.h"

#include "../common/liberror.h"
#include "protocol.h"

Sender::Sender(Socket& skt): protocol(skt) {}

void Sender::run() {
    try {
        while (!closed && _keep_running) {
            try {
                 Snapshot message = out_queue.pop();
                 protocol.send_snapshot(message, &closed);
            } catch (ClosedQueue& e) {
                return;
            }
        }
    } catch (LibError& e) {}
}

void Sender::stop() { out_queue.close(); }

Sender::~Sender() {}