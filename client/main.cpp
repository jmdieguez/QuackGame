#include <iostream>
#include "controller/game.h"
#include "model/protocol.h"
#include "view/main_window.h"
#include "model/lobby/lobby.h"
#include <QApplication>

#define OK 0
#define HOST 1
#define PORT 2
#define MIN_ARGS 3

int main(int argc, const char *argv[])
{
    if (argc != MIN_ARGS)
        return ERROR;

    try
    {
        QApplication app(argc, const_cast<char **>(argv));

        const char *host = argv[HOST];
        const char *port = argv[PORT];
        Socket skt(host, port);
        ClientProtocol protocol(skt);
        Lobby lobby(protocol);

        MainWindow w(&lobby);
        w.show();

        if (app.exec() == SUCCESS)
        {
            Game game(std::move(skt));
            game.run();
        }
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