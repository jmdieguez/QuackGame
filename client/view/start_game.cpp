
#include "start_game.h"
#include <QPushButton>
#include "ui_start_game.h"
#include "sound_player.h"
#include "window_utils.h"
#include "../ui/defs.h"
#include <QMessageBox>

void StartGame::set_info_user()
{
    QLabel *text = new QLabel(tr("Bienvenido al lobby del juego"), this);
    text->setAlignment(Qt::AlignCenter);
    text->setGeometry(0, 150, 780, 60);
    text->setStyleSheet("color: white;");
}

StartGame::StartGame(Lobby *lobby, QWidget *parent)
    : QDialog(parent), ui(new Ui::StartGame), lobby(lobby)
{
    ui->setupUi(this);
    WindowUtils::setFixedSize(this, 800, 600);
    WindowUtils::centerWindow(this);

    set_info_user();

    connect(ui->startButton, &QPushButton::clicked, this, [this]()
            {
        SoundPlayer::instance()->playSound(CLICK_SOUND, false);
        onStartButtonClicked(); });
}

StartGame::~StartGame()
{
    delete ui;
}

void StartGame::onStartButtonClicked()
{
    bool start;
    lobby->start_game(start);
    if (start)
    {
        closeAll();
    }
    else
    {
        QMessageBox::warning(this, tr("Game can not start."),
                             tr("Wait until other players join."));
    }
}

void StartGame::closeAll()
{
    QApplication::closeAllWindows();
}
