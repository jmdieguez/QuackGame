#include "main_window.h"
#include "lobby.h"

MainWindow::MainWindow(Lobby *lobby, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu),
    lobbyUI(lobby)
{

    connect(ui->CreateNewGame, &QPushButton::clicked, this, &MainWindow::on_createNewGameButton_clicked);
  //  connect(ui->startGameButton, &QPushButton::clicked, this, &MainWindow::on_startGameButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete lobbyUI;  // Liberar memoria de la vista de lobby si es necesario
}

void MainWindow::on_createNewGameButton_clicked()
{
    showLobby();
}

void MainWindow::on_startGameButton_clicked()
{
    // Aquí puedes iniciar el juego, abrir una nueva ventana o hacer lo necesario
}

void MainWindow::showLobby()
{
    // Mostrar la vista de lobby (si fuera necesario)
    lobbyUI->show();  // Esta línea muestra el widget de Lobby
    this->hide();     // Opcionalmente, puedes ocultar la ventana principal si la vista cambia completamente
}
