
#include "launcher.h"
#include "game.h"
#include "../model/protocol.h"
#include "../view/main_window.h"
#include "../view/game_result_window.h"
#include "../model/lobby/lobby.h"
#include <QApplication>
#define HOST 1
#define PORT 2
Launcher::Launcher(int argc, const char *argv[]): argc(argc), argv(argv) {
}

void Launcher::run_game() {
    QApplication app(argc, const_cast<char **>(argv));
    Socket skt(argv[HOST], argv[PORT]);
    ClientProtocol protocol(skt);
    Lobby lobby(protocol);

    MainWindow w(&lobby);
    w.show();
    bool result;
    if (app.exec() == SUCCESS) {
        Game game(std::move(skt));
        result = game.run();

        GameResultWindow resultWindow(result);
        resultWindow.exec();
    }
}