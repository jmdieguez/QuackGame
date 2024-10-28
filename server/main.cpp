#include "server.h"

// Uso: ./server <puerto>

#define PORT 1
#define SERVER_N_ARGS 2

int main(int argc, char *argv[])
{
    if (argc != SERVER_N_ARGS)
    {
        return ERROR;
    }
    else
    {
        const char *port = argv[PORT];

        Server server(port);
        return server.run();
    }
}
