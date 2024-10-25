#include "receiver.h"
#include "protocol.h"
#include "../common/liberror.h"
#include "client_command.h"

Receiver::Receiver(Socket& skt, const std::shared_ptr<Queue<ClientCommand>>& recv_q, uint16_t &id) :
        session_id(id), client(skt), recv_queue(recv_q), protocol(skt), closed(false){}

Receiver::~Receiver() {}

void Receiver::run() {
    try {
        while (!closed && _keep_running) {
            ActionMessage message = protocol.read_action();
            if (!closed) {
                try {
                    // Hace falta tener registro a qué cliente corresponde el msj
                    ClientCommand command(session_id, message);
                    recv_queue->push(command);
                } catch (ClosedQueue& e) {
                    return;
                }
            }
        }
    } catch (LibError& e) {}
}
