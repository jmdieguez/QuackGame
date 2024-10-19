#include "common_socket.h"
#include "common_thread.h"
#include "server_sessions_handler.h"

class Acceptor: public Thread {
private:
    Socket socket;
    SessionsHandler& handler;

public:
    explicit Acceptor(const char* port, SessionsHandler& h);
    virtual ~Acceptor();
    void stop() override;
    void run() override;
};
