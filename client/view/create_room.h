
#ifndef CREATE_ROOM_H
#define CREATE_ROOM_H


#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

#include "../model/lobby/lobby.h"

namespace Ui {
    class CreateRoom;
}

class CreateRoom : public QWidget
{
    Q_OBJECT

public:
    CreateRoom(Lobby *lobby, QWidget *parent = nullptr);
    ~CreateRoom();

    private slots:
        void onCreateButtonClicked();
        void onBackButtonClicked();

private:
    Ui::CreateRoom *ui;
    Lobby* lobby;
    QLineEdit *textBoxName;
    QPushButton *createButton;
};

#endif // CREATE_ROOM_H
