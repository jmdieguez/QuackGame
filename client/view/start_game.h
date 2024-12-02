
#ifndef START_GAME_H
#define START_GAME_H

#include <QDialog>
#include "../model/lobby/lobby.h"
#include <vector>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class StartGame;
}
QT_END_NAMESPACE

class StartGame : public QDialog
{
    Q_OBJECT

public:
    explicit StartGame(Lobby *lobby, std::vector<UserLobbyInfo>& users, QWidget* parent = nullptr);
    ~StartGame();


private slots:
    void onStartButtonClicked();
    void closeAll();
    // void onRoomCreated();

private:
    Ui::StartGame *ui;
    Lobby *lobby;
};

#endif // START_GAME_H
