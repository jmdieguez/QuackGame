
#include "start_game.h"
#include <QPushButton>
#include "ui_start_game.h"

StartGame::StartGame(Lobby* lobby, QWidget *parent)
    : QDialog(parent), ui(new Ui::StartGame), lobby(lobby)
{
    ui->setupUi(this);

    connect(ui->startButton, &QPushButton::clicked, this, &StartGame::onStartuttonClicked);
}

StartGame::~StartGame()
{
    delete ui;
}

void StartGame::onStartuttonClicked()
{
  // Añadir chequeo de que haya al menos 2 jugadores
    bool result = lobby->start_game();
    if (result) {
        closeAll();
    }
}


void StartGane::closeAll() {
    QApplication::closeAllWindows();
}