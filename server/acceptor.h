
#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <memory>
#include "../common/socket.h"
#include "../common/thread.h"
#include "session.h"

class Acceptor : public Thread {
private:
    Socket socket;
    uint16_t session_id;
    std::list<std::unique_ptr<Session>> sessions;
    void remove_disconnected_sessions();
    void remove_all_sessions();
public:
    explicit Acceptor(const char* port);
    virtual ~Acceptor();
    void stop() override;
    void run() override;
};
#endif  // ACCEPTOR_H