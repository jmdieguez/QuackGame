#include "create_room.h"
#include <QPushButton>
#include "ui_create_room.h"
CreateRoom::CreateRoom(Lobby* lobby, QWidget *parent)
    : QDialog(parent), ui(new Ui::CreateRoom), lobby(lobby)
{
    ui->setupUi(this);

    connect(ui->backButton, &QPushButton::clicked, this, &CreateRoom::onBackButtonClicked);
    connect(ui->createButton, &QPushButton::clicked, this, &CreateRoom::onCreateRoomButtonClicked);
}

CreateRoom::~CreateRoom()
{
    delete ui;
}

void CreateRoom::onBackButtonClicked()
{
    emit goBack();
}


void CreateRoom::onCreateRoomButtonClicked() {
    QString roomName = ui->textBoxName->text();
    lobby->create_room(roomName.toStdString());
    QApplication::closeAllWindows();
}