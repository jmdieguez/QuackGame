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
    displayResult(QString::fromStdString(playerColor));
}

void GameResultWindow::displayResult(const QString &playerColor) {
    SoundPlayer::instance()->playSound(VICTORY_SOUND, false);

    // Set window size and center it
    WindowUtils::setFixedSize(this, 800, 600);
    WindowUtils::centerWindow(this, VICTORY_BACKGROUND);

    // Update the label with the player color
    QString resultText = QString("Jugador: %1").arg(playerColor);
    ui->resultLabel->setText(resultText);

    // Load the custom font
    int fontId = QFontDatabase::addApplicationFont(FONT_PATH);
    if (fontId != -1) { // Font loaded successfully
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QFont customFont(fontFamily, 30); // Apply font with size 20
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
