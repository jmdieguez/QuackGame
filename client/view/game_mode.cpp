#include "game_mode.h"
#include "start_game.h"
#include <QPushButton>
#include "window_utils.h"
#include "sound_player.h"
#include "../ui/defs.h"
#include "ui_game_mode.h"

GameMode::GameMode(Lobby* lobby, QWidget* parent)
    : QDialog(parent),
      ui(new Ui::GameMode),
      lobby(lobby)
{
    ui->setupUi(this);
    WindowUtils::setFixedSize(this, 800, 600);
    WindowUtils::centerWindow(this, BACKGROUND);

    connect(ui->singlePlayerButton, &QPushButton::clicked, this, &GameMode::on_singlePlayerButton_clicked);

    connect(ui->multiplayerButton, &QPushButton::clicked, this, [this]() {
        SoundPlayer::instance()->playSound(CLICK_SOUND, false);
        on_multiplayerButton_clicked();
    });
}

void GameMode::on_singlePlayerButton_clicked() {
    lobby->prepare_single_player_game();
    display_start_game();
}

void GameMode::on_multiplayerButton_clicked() {
    lobby->prepare_multiplayer_game();
    display_start_game();
}

void GameMode::display_start_game() {
    try {
        std::vector<UserLobbyInfo>& result = lobby->send_create_game();
        if (result.empty()) {
            std::cout << "llega vacia" << std::endl;
            return;
        }
        StartGame* startGameDialog = new StartGame(lobby, result, this);
        this->hide();
        startGameDialog->exec();
    } catch (const std::exception& e) {
    }
}


GameMode::~GameMode() {
    delete ui;
}

