
#ifndef GAME_MODE_H
#define GAME_MODE_H

#include <QDialog>
#include "../model/lobby/lobby.h"
#include "start_game.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class GameMode;
}
QT_END_NAMESPACE

class GameMode : public QDialog {
    Q_OBJECT

public:
    explicit GameMode(Lobby* lobby, const bool& create, QWidget* parent = nullptr);
    ~GameMode();

    private slots:
    void on_singlePlayerButton_clicked();
    void on_multiplayerButton_clicked();

private:
    Ui::GameMode* ui;
    Lobby* lobby;
    bool create_game = false;
    StartGame* startGameWindow = nullptr;
    void display_start_game();
    void create_new_game();
    void join_existing_game();
};



#endif //GAME_MODE_H
