#include "main_window.h"
#include "ui_main_window.h"
#include <QMessageBox>

MainWindow::MainWindow(Lobby* lobby, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), lobby(lobby), create_room(new CreateRoom(lobby, this))
{
    ui->setupUi(this);
    create_room->hide();
    connect(ui->createButton, &QPushButton::clicked, this, &MainWindow::onCreateButtonClicked);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::onExitButtonClicked);
    connect(ui->JoinButton, &QPushButton::clicked, this, &MainWindow::onJoinButtonClicked);
}

void MainWindow::onCreateButtonClicked()
{
    // Oculta la ventana principal
    this->hide();
    create_room->show();
}

void MainWindow::onExitButtonClicked()
{
    close();  // Cierra la ventana
}

void MainWindow::onJoinButtonClicked()
{
    QMessageBox::information(this, "Join", "Join button was clicked.");
}
MainWindow::~MainWindow()
{
    delete create_room;  // Liberar la memoria asignada
     delete ui;
}