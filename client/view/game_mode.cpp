#include "game_mode.h"
#include "start_game.h"
#include <QPushButton>
#include "window_utils.h"
#include "sound_player.h"
#include "../ui/defs.h"
#include "ui_game_mode.h"
#include <vector>

GameMode::GameMode(Lobby* lobby, const bool& create, QWidget* parent)
    : QDialog(parent),
      ui(new Ui::GameMode),
      lobby(lobby),
      create_game(create)
{
    ui->setupUi(this);
    WindowUtils::setFixedSize(this, 800, 600);
    WindowUtils::centerWindow(this, BACKGROUND);


    connect(ui->singlePlayerButton, &QPushButton::clicked, this, [this]() {
         SoundPlayer::instance()->playSound(CLICK_SOUND, false);
         on_singlePlayerButton_clicked();
     });
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
    if (create_game) {
        create_new_game();
    } else {
        join_existing_game();
    }
}

void GameMode::create_new_game() {
    std::vector<UserLobbyInfo> result = lobby->send_create_game();
    if (result.empty()) {
        return;
    }

    this->hide();

    if (!startGameWindow) {
        startGameWindow = new StartGame(lobby, result, nullptr);
        startGameWindow->setAttribute(Qt::WA_DeleteOnClose);

        connect(startGameWindow, &QDialog::finished, this, [this]() {
            startGameWindow->deleteLater();
            startGameWindow = nullptr;
        });
    }

    startGameWindow->show();
}

void GameMode::join_existing_game() {
    lobby->join_room();
    QApplication::closeAllWindows();
}

GameMode::~GameMode() {
    delete ui;
}

