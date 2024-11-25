#include "create_room.h"
#include <QPushButton>
#include "ui_create_room.h"
#include <QThread>
#include "start_game.h"
#include "sound_player.h"
#include "window_utils.h"
#include "../ui/defs.h"

CreateRoom::CreateRoom(Lobby* lobby, QWidget *parent)
    : QDialog(parent), ui(new Ui::CreateRoom), lobby(lobby)
{
    ui->setupUi(this);
    WindowUtils::setFixedSize(this, 800, 600);
    WindowUtils::centerWindow(this);


    connect(ui->backButton, &QPushButton::clicked, this, [this]() {
        SoundPlayer::instance()->playSound(CLICK_SOUND, false);
        onBackButtonClicked();
    });

    connect(ui->createButton, &QPushButton::clicked, this, [this]() {
        SoundPlayer::instance()->playSound(CLICK_SOUND, false);
        onCreateRoomButtonClicked();
    });
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
    this->hide();
    StartGame startDialog(lobby, nullptr);
    startDialog.exec();

    QApplication::closeAllWindows();
}