#ifndef CREATE_ROOM_H
#define CREATE_ROOM_H

#include <QDialog>
#include "../model/lobby/lobby.h"
#include "game_mode.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class CreateRoom;
}
QT_END_NAMESPACE

class CreateRoom : public QDialog
{
    Q_OBJECT

public:
    explicit CreateRoom(Lobby* lobby, QWidget *parent = nullptr);
    ~CreateRoom();

    signals:
        void goBack();
        void roomCreated();

    private slots:
        void onBackButtonClicked();
        void onCreatSinglePlayerClicked();
        void onCreateMUltiplayerButtonClicked();

private:
    Ui::CreateRoom *ui;
    Lobby* lobby;
    GameMode* gameModeWindow = nullptr;
};

#endif // CREATE_ROOM_H