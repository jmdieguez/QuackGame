
#include "start_game.h"
#include <QPushButton>
#include "ui_start_game.h"
#include "window_utils.h"
#include "../ui/defs.h"
#include <QMessageBox>

#include <QListWidgetItem>

StartGame::StartGame(Lobby *lobby, std::vector<UserLobbyInfo>& users, QWidget *parent)
    : QDialog(parent), ui(new Ui::StartGame), lobby(lobby) {
    ui->setupUi(this);

    WindowUtils::setFixedSize(this, 800, 600);
    WindowUtils::centerWindow(this, BACKGROUND);
    ui->userListWidget->clear();  // Limpiar la lista de usuarios
    for (size_t i = 0; i < users.size(); ++i) {
        std::string userInfo = "Player " + std::to_string(i + 1) + ": " + users[i].get_color();
        QString qUserInfo = QString::fromStdString(userInfo);

        ui->userListWidget->addItem(qUserInfo);
    }

    connect(ui->startButton, &QPushButton::clicked, this, [this]() {
        onStartButtonClicked();
    });
}

void StartGame::onStartButtonClicked() {
    bool start;
    lobby->start_game(start);
    if (start) {
        closeAll();
    } else {
        QMessageBox::warning(this, tr("Game cannot start."),
                             tr("Wait until other players join."));
    }
}

void StartGame::closeAll() {
    QApplication::closeAllWindows();
}

StartGame::~StartGame() {
    delete ui;
}