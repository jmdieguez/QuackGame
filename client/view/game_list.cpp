
#include "game_list.h"
#include "ui_game_list.h"
#include <iostream>
#include <QStringList>
#include <QCloseEvent>
#include "sound_player.h"
#include "window_utils.h"
#include "../ui/defs.h"


GameList::GameList(Lobby* lobby, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameList),
    lobby(lobby)
{
    ui->setupUi(this);
    WindowUtils::setFixedSize(this, 800, 600);
    WindowUtils::centerWindow(this, BACKGROUND);

    connect(ui->listWidget, &QListWidget::itemClicked, this, [this](QListWidgetItem* item) {
        SoundPlayer::instance()->playSound(CLICK_SOUND, false);
        onItemClicked(item);
    });

    connect(ui->back, &QPushButton::clicked, this, [this]() {
        SoundPlayer::instance()->playSound(CLICK_SOUND, false);
        onBackButtonClicked();
    });
}


void GameList::setGameList(const std::map<uint16_t, std::string>& games)
{
    QStringList gameNames;

    ui->listWidget->clear();
    nameToIdMap.clear();
    if (games.size() > 0) {
        for (const auto& game : games) {
            QString qName = QString::fromStdString(game.second);
            gameNames.append(qName);

            ui->listWidget->addItem(qName);

            nameToIdMap[qName] = game.first;
        }
    } else {
        QListWidgetItem* noGamesItem = new QListWidgetItem("No games available. Create a new match to start playing!");
        noGamesItem->setTextAlignment(Qt::AlignCenter);
        noGamesItem->setFlags(noGamesItem->flags() & ~Qt::ItemIsSelectable);
        ui->listWidget->addItem(noGamesItem);
    }
}

void GameList::onItemClicked(QListWidgetItem* item)
{
    QString gameName = item->text();
    if (nameToIdMap.count(gameName) > 0) {
        uint16_t gameId = nameToIdMap[gameName];
        lobby->join_room(gameId);
        QApplication::closeAllWindows();
    }
}

void GameList::onBackButtonClicked()
{
    emit goBack();
}


void GameList::closeEvent(QCloseEvent* event)
{
    emit closed();
    event->accept();
    delete ui;
}

GameList::~GameList()
{
    delete ui;
}