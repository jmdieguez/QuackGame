
#include "launcher.h"
#include "game.h"
#include "../model/protocol.h"
#include "../view/main_window.h"
#include "../view/game_result_window.h"
#include "../model/lobby/lobby.h"
#include <QApplication>
#define HOST 1
#define PORT 2
Launcher::Launcher(int argc, const char *argv[]) : argc(argc), argv(argv)
{
}

void Launcher::run_game()
{
    QApplication app(argc, const_cast<char **>(argv));
    Socket skt(argv[HOST], argv[PORT]);
    ClientProtocol protocol(skt);
    Lobby lobby(protocol);
    MainWindow w(&lobby);
    w.show();

    std::string winning_color;
    if (app.exec() == SUCCESS)
    {
        std::vector<UserLobbyInfo> users = lobby.get_users();
        if (!users.empty()) {
            Game game(std::move(skt), users);
            game.run(winner);
        }
        show_result();
    }
    return;
}

void Launcher::show_result() {
    if (!winner.empty()) {
        GameResultWindow resultWindow(winner);
        resultWindow.exec();
    }
}