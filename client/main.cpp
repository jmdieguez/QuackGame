#include <iostream>
#include "controller/game.h"
#include "model/resource/texturefactory.h"
#include "model/protocol.h"
#include "controller/lobby/lobby.h"
#include "controller/lobby/main_window.h"
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
        const char *host = argv[HOST];
        const char *port = argv[PORT];
        Socket socket(host, port);
        ClientProtocol protocol(socket);

        Lobby lobby(protocol);
        QApplication app(argc,  const_cast<char**>(argv));
        MainWindow w(&lobby);
        w.show();
        app.exec();
       // Game game(host, port);
       //    game.run();

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