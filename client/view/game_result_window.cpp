#include "game_result_window.h"
#include "window_utils.h"
#include "sound_player.h"
#include "../ui/defs.h"
#include <QString>
#include <QFontDatabase>
#include <QFont>

GameResultWindow::GameResultWindow(const std::string& playerColor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameResultWindow) {
    ui->setupUi(this);
    connect(ui->exitButton, &QPushButton::clicked, this, &GameResultWindow::onExitButtonClicked);
    if (!playerColor.empty()) {
        displayResult(QString::fromStdString(playerColor));
    }
}

void GameResultWindow::displayResult(const QString &playerColor) {
    SoundPlayer::instance()->playSound(VICTORY_SOUND, false);

    WindowUtils::setFixedSize(this, 800, 600);
    WindowUtils::centerWindow(this, VICTORY_BACKGROUND);

    QString resultText = QString("Jugador: %1").arg(playerColor);
    ui->resultLabel->setText(resultText);

    int fontId = QFontDatabase::addApplicationFont(FONT_PATH);
    if (fontId != -1) {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QFont customFont(fontFamily, 30);
        ui->resultLabel->setFont(customFont);
        ui->resultLabel->setStyleSheet("color: yellow;");

    } else {
        qWarning("Failed to load font from %s", FONT_PATH);
    }
}

GameResultWindow::~GameResultWindow() {
    delete ui;
}

void GameResultWindow::onExitButtonClicked() {
    QApplication::quit();
}
