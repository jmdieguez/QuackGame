#include <iostream>
#include "controller/game.h"
#include "model/resource/texturefactory.h"
#include "model/protocol.h"
#include "view/main_window.h"
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
        // Create QApplication with the const_cast to remove the const qualifier from argv
        QApplication app(argc, const_cast<char**>(argv)); // Cast const char** to char**

      // const char *host = argv[HOST];
      // const char *port = argv[PORT];

  //      Lobby lobby;
//
        // Create MainWindow after QApplication
        MainWindow w;
        w.show();

        // Enter Qt event loop
        return app.exec();  // Start event loop

        // Game game(host, port); // Game logic can be executed later, if needed.
        // game.run();

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