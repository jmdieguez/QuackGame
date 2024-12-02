#include "main_window.h"
#include "ui_main_window.h"
#include <QPushButton>
#include "window_utils.h"
#include "sound_player.h"
#include "../ui/defs.h"

MainWindow::MainWindow(Lobby* lobby, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), lobby(lobby) {
    ui->setupUi(this);

    WindowUtils::setFixedSize(this, 800, 600);
    WindowUtils::centerWindow(this, BACKGROUND);

    connect(ui->createButton, &QPushButton::clicked, this, [this]() {
        SoundPlayer::instance()->playSound(CLICK_SOUND, false);
        onCreateButtonClicked();
    });

    connect(ui->exitButton, &QPushButton::clicked, this, [this]() {
        SoundPlayer::instance()->playSound(CLICK_SOUND, false);
        onExitButtonClicked();
    });

    connect(ui->joinButton, &QPushButton::clicked, this, [this]() {
        SoundPlayer::instance()->playSound(CLICK_SOUND, false);
        onJoinButtonClicked();
    });
}

void MainWindow::onCreateButtonClicked()
{
    create_room = new CreateRoom(lobby, nullptr);
    create_room->setAttribute(Qt::WA_DeleteOnClose);

    connect(create_room, &CreateRoom::goBack, this, [this]() {
    this->onBackToMainWindow(create_room);
    });

    this->hide();
    create_room->show();
}

void MainWindow::onBackToMainWindow(QWidget* window)
{
    if (window) {
        window->hide();
    }
    this->show();
}
void MainWindow::onExitButtonClicked()
{
    close();
}

void MainWindow::onJoinButtonClicked()
{
    std::map<uint16_t, std::string> games;
    lobby->get_game_list(games);
    if (!gameListWindow) {
        gameListWindow = new GameList(lobby);
        gameListWindow->setGameList(games);

        connect(gameListWindow, &GameList::goBack, this, [this]() {
            this->onBackToMainWindow(gameListWindow);
        });

        this->hide();
        gameListWindow->show();
    }
}
void MainWindow::onGameListClosed()
{
    this->show();
    delete gameListWindow;
    gameListWindow = nullptr;
}
MainWindow::~MainWindow()
{
    delete ui;
}
