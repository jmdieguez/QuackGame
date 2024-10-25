#include "sender.h"

#include "../../common/liberror.h"
#include "protocol.h"
#include <cstdint>
#include <iostream>


Sender::Sender(Socket& skt, Queue<ClientActionType>& queue):  protocol(skt), queue_sender(queue), closed(false) {}

void Sender::run() {
    try {
        while (!closed && _keep_running) {
            try {
                 ClientActionType action = queue_sender.pop();
                 protocol.send_action(action, closed);
            } catch (ClosedQueue& e) {
                return;
            }
        }
    } catch (LibError& e) {}
}

void Sender::stop() {  queue_sender.close(); }

Sender::~Sender() {}