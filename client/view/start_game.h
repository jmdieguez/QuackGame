
#ifndef START_GAME_H
#define START_GAME_H

#include <QDialog>
#include "../model/lobby/lobby.h"

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
    explicit StartGame(Lobby *lobby, QWidget *parent = nullptr);
    ~StartGame();

signals:
    void goBack();

private slots:
    void onStartButtonClicked();
    void closeAll();
    // void onRoomCreated();

private:
    Ui::StartGame *ui;
    Lobby *lobby;

    void set_info_user();
};

#endif // START_GAME_H
