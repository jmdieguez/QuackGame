#include "main_window.h"
#include "ui_main_window.h"
#include <QMessageBox>
#include <QPushButton>
#include <QIcon>

#define ICON_PATH "/var/quackgame/logo.png"

MainWindow::MainWindow(Lobby* lobby, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), lobby(lobby)
{
    ui->setupUi(this);

    connect(ui->createButton, &QPushButton::clicked, this, &MainWindow::onCreateButtonClicked);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::onExitButtonClicked);
    connect(ui->joinButton, &QPushButton::clicked, this, &MainWindow::onJoinButtonClicked);

    QIcon icon(ICON_PATH);
    setWindowIcon(icon);
}

void MainWindow::onCreateButtonClicked()
{
    create_room = new CreateRoom(lobby, nullptr);
    create_room->setAttribute(Qt::WA_DeleteOnClose);

    connect(create_room, &CreateRoom::goBack, this, &MainWindow::onBackToMainWindow);

    this->hide();
    create_room->show();
}

void MainWindow::onBackToMainWindow()
{
    create_room->hide();
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
    GameList* gameListWindow = new GameList(lobby);
    gameListWindow->setGameList(games);
    gameListWindow->show();
}
void MainWindow::onGameListClosed()
{
    this->show();
}
MainWindow::~MainWindow()
{
    delete ui;
}
