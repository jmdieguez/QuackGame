#include "lobby.h"
#include <QDebug>
#include "../../view/create_room.h"

Lobby::Lobby(ClientProtocol& p, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateRoom),
    protocol(p)
{
    ui->setupUi(this);

  //  connect(ui->pushButton, &QPushButton::clicked, this, &Lobby::on_createButton_clicked);

 //   connect(ui->pushButton_2, &QPushButton::clicked, this, &Lobby::on_backButton_clicked);
}

void Lobby::on_createButton_clicked()
{
    QString roomName = ui->lineEdit->text();

    if (!roomName.isEmpty()) {
        qDebug() << "Room created with name:" << roomName;
    } else {
        qDebug() << "Please enter a room name.";
    }
}

void Lobby::on_backButton_clicked()
{
    this->close();


    QWidget *parentWindow = this->parentWidget();
    if (parentWindow) {
        parentWindow->show();
    }
}


Lobby::~Lobby()
{
    delete ui;
}
