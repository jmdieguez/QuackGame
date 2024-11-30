
#include "launcher.h"
#include "controller/game.h"
#include "model/protocol.h"
#include "view/main_window.h"
#include "model/lobby/lobby.h"
#include <QApplication>

Launcher::Launcher(const char* h, const char*p): host(h), port(p) {}

void Launcher::run_game() {
    QApplication app(argc, const_cast<char **>(argv));
    Socket skt(host, port);
    ClientProtocol protocol(skt);
    Lobby lobby(protocol);

    MainWindow w(&lobby);
    w.show();
    bool result;
    if (app.exec() == SUCCESS)
    {
        Game game(std::move(skt));
        result = game.run();
    }
}