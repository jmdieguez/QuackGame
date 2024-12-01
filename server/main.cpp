#include "server.h"
#include "../common/config.h"

// Uso: ./server <puerto>
#define PORT 1
#define SERVER_N_ARGS 2
#define CONFIG_PATH "config/server.yaml"

int main(int argc, char *argv[])
{
    if (argc != SERVER_N_ARGS)
    {
        return ERROR;
    }
    else
    {
        const char *port = argv[PORT];
        Config::getInstance().load(CONFIG_PATH);
        Server server(port);
        return server.run();
    }
}
