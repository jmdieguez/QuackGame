#include "sessions_handler.h"
#include <algorithm>
#include <sstream>
#include <utility>
#include "../common/liberror.h"


void SessionsHandler::add(Queue<Snapshot>& queue, uint16_t id) {
    std::unique_lock<std::mutex> lck(mtx);
    clients_queues.push_back(std::make_pair(std::ref(queue), id));
}

void SessionsHandler::broadcast(const Snapshot& message) {
    std::unique_lock<std::mutex> lck(mtx);
    if (clients_queues.size() == 0) {
        return;
    } else {
        for (auto& pair: clients_queues) {
            Queue<Snapshot>& queue = pair.first;
            try {
                queue.try_push(message);
            } catch (const ClosedQueue&) {}
        }
    }
}

void SessionsHandler::remove_client(const uint16_t& id) {
    std::unique_lock<std::mutex> lck(mtx);
    auto it = clients_queues.begin();
    while (it != clients_queues.end()) {
        uint8_t idQueue = it->second;
        if (idQueue == id) {
            it = clients_queues.erase(it);
        } else {
            ++it;
        }
    }
}

SessionsHandler::~SessionsHandler() {}