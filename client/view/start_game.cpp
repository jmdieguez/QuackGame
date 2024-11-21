
#include "start_game.h"
#include <QPushButton>
#include "ui_start_game.h"
#include "sound_player.h"
#include "window_utils.h"
#include "../ui/defs.h"

StartGame::StartGame(Lobby* lobby, QWidget *parent)
    : QDialog(parent), ui(new Ui::StartGame), lobby(lobby)
{
    ui->setupUi(this);
    WindowUtils::setFixedSize(this, 800, 600);
    WindowUtils::centerWindow(this);
    connect(ui->startButton, &QPushButton::clicked, this, [this]() {
        SoundPlayer::instance()->playSound(CLICK_SOUND, false);
        onStartButtonClicked();
    });
}

StartGame::~StartGame()
{
    delete ui;
}

void StartGame::onStartButtonClicked()
{
    lobby->start_game();
    closeAll();
}


void StartGame::closeAll() {
    QApplication::closeAllWindows();
}