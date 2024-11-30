
#include "start_game.h"
#include <QPushButton>
#include "ui_start_game.h"
#include "sound_player.h"
#include "window_utils.h"
#include "../ui/defs.h"
#include <QMessageBox>
void StartGame::set_info_user(size_t &index, std::string &color, int x_position, int y_position)
{
    std::string text_color("Player ");
    std::string text_color_index = text_color + std::to_string(index + 1);
    std::string text_color_index_name = text_color_index + " : " + color;
    QLabel *text = new QLabel(tr(text_color_index_name.c_str()), this);
    text->setAlignment(Qt::AlignCenter);
    text->setGeometry(x_position, y_position, 200, 60);
    text->setStyleSheet("color: white;");
}

StartGame::StartGame(Lobby *lobby, std::vector<UserLobbyInfo> &users, QWidget *parent)
    : QDialog(parent), ui(new Ui::StartGame), lobby(lobby)
{
    ui->setupUi(this);
    WindowUtils::setFixedSize(this, 800, 600);
    WindowUtils::centerWindow(this);

    int y_position = 150;
    int x_spacing = 250;
    int total_width = (users.size() - 1) * x_spacing + 200;
    int x_offset = (800 - total_width) / 2;

    for (size_t i = 0; i < users.size(); i++)
    {
        std::string color = users[i].get_color();
        set_info_user(i, color, x_offset + i * x_spacing, y_position);
    }

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
