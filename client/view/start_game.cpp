
#include "start_game.h"
#include <QPushButton>
#include "ui_start_game.h"

StartGame::StartGame(Lobby* lobby, QWidget *parent)
    : QDialog(parent), ui(new Ui::StartGame), lobby(lobby)
{
    ui->setupUi(this);

    connect(ui->startButton, &QPushButton::clicked, this, &StartGame::onStartButtonClicked);
}

StartGame::~StartGame()
{
    delete ui;
}

void StartGame::onStartButtonClicked()
{
  // Añadir chequeo de que haya al menos 2 jugadores
    lobby->start_game();
    closeAll();
}


void StartGame::closeAll() {
    QApplication::closeAllWindows();
}