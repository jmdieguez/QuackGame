#include "main_window.h"
#include "ui_main_window.h"
#include <QMessageBox>
#include <QPushButton>

MainWindow::MainWindow(Lobby* lobby, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), lobby(lobby)
{
    ui->setupUi(this);

    connect(ui->createButton, &QPushButton::clicked, this, &MainWindow::onCreateButtonClicked);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::onExitButtonClicked);
    connect(ui->JoinButton, &QPushButton::clicked, this, &MainWindow::onJoinButtonClicked);
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
  // TODO: aca va a estar asociado con GameLists
    QMessageBox::information(this, "Join", "Join button was clicked.");
}

MainWindow::~MainWindow()
{
    delete ui;
}
