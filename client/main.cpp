#include "controller/game.h"
#include "model/resource/texturefactory.h"

#define OK 0
#define ERROR 1
#define HOST 1
#define PORT 2
#define MIN_ARGS 3

int main(int argc, const char *argv[])
{

    if (argc != MIN_ARGS)
        return ERROR;

    try
    {
        const char *host = argv[HOST];
        const char *port = argv[PORT];

        Game game(host, port);
        game.run();

        return OK;
    }
    catch (const std::exception &err)
    {
        std::cerr << "Something went wrong and an exception was caught: " << err.what()
                  << std::endl;
        return ERROR;
    }
    catch (...)
    {
        std::cerr << "Something went wrong and an unknown exception was caught." << std::endl;
        return ERROR;
    }
    return OK;
}