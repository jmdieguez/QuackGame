
#include "game_result_window.h"
#include "window_utils.h"
#include "sound_player.h"
#include "../ui/defs.h"
#include <QString>

GameResultWindow::GameResultWindow(bool victory, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameResultWindow) {
    ui->setupUi(this);
    connect(ui->exitButton, &QPushButton::clicked, this, &GameResultWindow::onExitButtonClicked);
    displayResult(victory);
}

void GameResultWindow::displayResult(bool victory) {
    QString back = victory ? VICTORY_BACKGROUND : DEFEAT_BACKGROUND;
    QString sound = victory ? VICTORY_SOUND : DEFEAT_SOUND;
    SoundPlayer::instance()->playSound(sound, false);
    WindowUtils::setFixedSize(this, 800, 600);
    WindowUtils::centerWindow(this, back);
}

GameResultWindow::~GameResultWindow() {
    delete ui;
}

void GameResultWindow::onExitButtonClicked() {
    QApplication::quit();
}