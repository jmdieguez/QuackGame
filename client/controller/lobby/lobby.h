#ifndef LOBBY_H
#define LOBBY_H

#include <QWidget>
#include "../../model/protocol.h"
#include "../../view/create_room.h"



class Lobby : public QWidget
{
    Q_OBJECT

public:
    explicit Lobby(ClientProtocol& protocol, QWidget *parent = nullptr);
    ~Lobby();

    private slots:
        void on_createButton_clicked();
        void on_backButton_clicked();

private:
    Ui::CreateRoom *ui;
    ClientProtocol& protocol;
};

#endif // LOBBY_H
