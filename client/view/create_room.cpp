#include "create_room.h"
#include <QPushButton>
#include "ui_create_room.h"
#include <QThread>
#include "sound_player.h"
#include "window_utils.h"
#include "start_game.h"
#include "../ui/defs.h"

CreateRoom::CreateRoom(Lobby *lobby, QWidget *parent)
    : QDialog(parent), ui(new Ui::CreateRoom), lobby(lobby)
{
    ui->setupUi(this);
    WindowUtils::setFixedSize(this, 800, 600);
    WindowUtils::centerWindow(this, BACKGROUND);

    connect(ui->backButton, &QPushButton::clicked, this, [this]()
            {
        SoundPlayer::instance()->playSound(CLICK_SOUND, false);
        onBackButtonClicked(); });

    connect(ui->createMUltiplayerButton, &QPushButton::clicked, this, [this]() {
        SoundPlayer::instance()->playSound(CLICK_SOUND, false);
        onCreateMUltiplayerButtonClicked();
    });
    connect(ui->creatSinglePlayer, &QPushButton::clicked, this, [this]() {
        SoundPlayer::instance()->playSound(CLICK_SOUND, false);
        onCreatSinglePlayerClicked();
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


void CreateRoom::onCreatSinglePlayerClicked() {
    QString roomName = ui->textBoxName->text();
    lobby->prepare_single_player_game();
    std::vector<UserLobbyInfo> result = lobby->create_room(roomName.toStdString());
    this->hide();
    StartGame startDialog(lobby, result, nullptr);
    startDialog.exec();

    QApplication::closeAllWindows();
}

void CreateRoom::onCreateMUltiplayerButtonClicked() {
    QString roomName = ui->textBoxName->text();
    lobby->prepare_multiplayer_game();
    std::vector<UserLobbyInfo> result = lobby->create_room(roomName.toStdString());
    this->hide();
    StartGame startDialog(lobby, result, nullptr);
    startDialog.exec();

    QApplication::closeAllWindows();
}

