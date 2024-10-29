#include "acceptor.h"

#include <memory>

#include "../common/liberror.h"
#include "session.h"

Acceptor::Acceptor(const char *port, SessionsHandler &h) : socket(port), handler(h) {}

Acceptor::~Acceptor() {}

void Acceptor::stop()
{

    _keep_running = false;
    socket.shutdown(2);
    socket.close();
    handler.remove_all_sessions();
}

void Acceptor::run()
{
    try
    {
        while (_keep_running.load())
        {
            Socket client = socket.accept();
            handler.add(client);
            handler.remove_closed_sessions();
        }
    }
    catch (LibError &e)
    {
    }
}
