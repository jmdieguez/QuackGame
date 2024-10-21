#include "../common/socket.h"
#include "../common/thread.h"
#include "sessions_handler.h"

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
