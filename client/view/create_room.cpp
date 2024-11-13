#include "create_room.h"
#include "ui_create_room.h"
#include <QMessageBox>
#include "main_window.h"
CreateRoom::CreateRoom(Lobby *lobby, QWidget *parent)
    : QWidget(parent), ui(new Ui::CreateRoom), lobby(lobby),  textBoxName(new QLineEdit(this)),
      createButton(new QPushButton("Create", this))
{
    ui->setupUi(this);
    connect(ui->backButton, &QPushButton::clicked, this, &CreateRoom::onBackButtonClicked);
    connect(ui->createButton, &QPushButton::clicked, this, &CreateRoom::onBackButtonClicked);
}

CreateRoom::~CreateRoom()
{
    delete ui;
}

void CreateRoom::onCreateButtonClicked()
{
    QString roomName = textBoxName->text();
    if (roomName.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Please, insert a valid name");
        return;
    }
    lobby->createRoom(roomName.toStdString());
}

void CreateRoom::onBackButtonClicked()
{
    this->hide();
    if (auto main_window = qobject_cast<MainWindow*>(parent())) {
        main_window->show();
    }
}